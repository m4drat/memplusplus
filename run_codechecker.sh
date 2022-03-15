#!/bin/bash

CodeChecker server --workspace ./codechecker-ws &
CodeChecker store .codechecker --name mem++ --url http://localhost:8001/Default
