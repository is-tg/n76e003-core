package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
)

func main() {
	if len(os.Args) < 2 {
		log.Fatal("hello there")
	}

	var err error

	switch os.Args[1] {
	case "pp":
		err = runPreprocessor(os.Args[2:])
	case "ld":
		err = runLinker(os.Args[2:])
	default:
		log.Fatalf("dunno %s", os.Args[1])
	}

	if err != nil {
		log.Fatal(err)
	}
}

func runPreprocessor(args []string) error {
	props, err := parseCompilerArgs(args)
	if err != nil {
		return err
	}

	/* Skip dependency file generation */
	if strings.HasSuffix(props.Output, "libsdetect.d") {
		return nil
	}

	/* Not relying on -o for -E */
	cmdArgs := append(props.Includes, "-x", "c", "-E", props.Source)

	out, err := runProgram("sdcc", cmdArgs...)
	if err != nil {
		return err
	}

	return os.WriteFile(props.Output, out, 0644)
}

const mainObject = "main.c.o"

func runLinker(args []string) error {
	props, err := parseLinkerArgs(args)
	if err != nil {
		return err
	}

	/* Extract main.c.o */
	err = extractMain(props.Archive)
	if err != nil {
		return err
	}

	/* Rename extensions */
	props.Main, err = tempCopy(mainObject, "rel")
	if err != nil {
		return err
	}
	os.Remove(mainObject)
	defer os.Remove(props.Main)

	props.Archive, err = tempCopy(props.Archive, "lib")
	if err != nil {
		return err
	}
	defer os.Remove(props.Archive)

	props.Object, err = tempCopy(props.Object, "rel")
	if err != nil {
		return err
	}
	defer os.Remove(props.Object)

	/* Link */
	cmdArgs := []string{
		"-mmcs51",
		"--model-small",
		"--iram-size", "256",
		"--xram-size", "768",
		"--code-size", "18432",
		props.Main, props.Object,
		props.Archive,
		"-o", props.Program,
	}

	_, err = runProgram("sdcc", cmdArgs...)
	if err != nil {
		if isExpectedLinkerError(err.Error()) {
			return nil
		}

		return err
	}

	return nil
}

func extractMain(archive string) error {
	_, err := runProgram("sdar", "-x", archive, mainObject)
	return err
}

func tempCopy(filename string, extension string) (string, error) {
	src, err := os.Open(filename)
	if err != nil {
		return "", err
	}
	defer src.Close()

	temp, err := os.CreateTemp("", filepath.Base(filename)+"*."+extension)
	if err != nil {
		return "", err
	}
	defer temp.Close()

	_, err = io.Copy(temp, src)
	if err != nil {
		return "", err
	}

	return temp.Name(), nil
}

func isExpectedLinkerError(data string) bool {
	scanner := bufio.NewScanner(strings.NewReader(data))

	/* Skip first line */
	if !scanner.Scan() {
		return false
	}

	for scanner.Scan() {
		line := scanner.Text()

		if strings.HasPrefix(line, "?ASlink-Error-<cannot open>") {

			if strings.HasPrefix(line, ".lst\"") {
				continue
			}
		}

		return false
	}

	return scanner.Err() == nil
}

func runProgram(prog string, args ...string) ([]byte, error) {
	cmd := exec.Command(prog, args...)
	out, err := cmd.CombinedOutput()
	if err != nil {
		return out, fmt.Errorf("%s: %w\n%s", prog, err, out)
	}

	return out, nil
}

type CompilerArgs struct {
	Includes []string
	Source   string
	Output   string
}

type LinkerArgs struct {
	Main    string
	Object  string
	Archive string
	Program string
}

func parseCompilerArgs(args []string) (CompilerArgs, error) {
	n := len(args)

	if n < 3 {
		return CompilerArgs{}, fmt.Errorf("not enough arguments")
	}

	return CompilerArgs{
		Includes: args[:n-2],
		Source:   args[n-2],
		Output:   args[n-1],
	}, nil
}

func parseLinkerArgs(args []string) (LinkerArgs, error) {
	if len(args) < 3 {
		return LinkerArgs{}, fmt.Errorf("not enough arguments")
	}

	return LinkerArgs{
		Object:  args[0],
		Archive: args[1],
		Program: args[2],
	}, nil
}
