#!/bin/bash

set -e

cmake .. && make && ./build/bin/TwofishPDFEncryptor
