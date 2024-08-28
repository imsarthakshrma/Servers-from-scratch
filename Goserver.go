package main

import (
	"fmt"
	"net/http"
)

func helloHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, "Hello World! This is my first very own server")

}

func main() {
	http.HandleFunc("/", helloHandler) // Route for handaling requests

	fmt.Println("Server is listening on port 3030")
	if err := http.ListenAndServe(":3030", nil); err != nil {
		fmt.Println("Failed to start server:", err)
	}
}
