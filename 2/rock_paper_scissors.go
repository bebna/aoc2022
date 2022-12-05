package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"os"
	"strings"
)

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		log.Fatal(err)	
	}
	defer file.Close()

	fmt.Println(handle_input(strings.NewReader("A Y\nB X\nC Z")))
	fmt.Println(handle_input(file))
}

func handle_input(input io.Reader) uint {
	sum := uint(0)
	selection_points := map[string]uint{"X":0, "Y":3, "Z":6}
	outcome_points := map[string]map[string]uint{
		"A":{"X":3,"Y":1,"Z":2},
		"B":{"X":1,"Y":2,"Z":3},
		"C":{"X":2,"Y":3,"Z":1},
	}
	scanner := bufio.NewScanner(input)
	scanner.Split(bufio.ScanLines)
	for scanner.Scan() {
		round := strings.Split(scanner.Text(), " ")
		sum += selection_points[round[1]] + outcome_points[round[0]][round[1]]
	}
	return sum
}
