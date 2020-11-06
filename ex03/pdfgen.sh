#!/bin/bash

# ref: https://tonooo71.github.io/2018/180619_enscript/180619_enscript/

if [ $# -eq 1 ]; then
	filename=$1
	enscript --highlight=c --color -C -H1 $filename -o $filename.ps
	ps2pdf $filename.ps
	rm $filename.ps
fi