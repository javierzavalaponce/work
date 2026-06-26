#!/bin/bash
pandoc \
  --metadata-file=../config.yaml \
  -B portada.md \
  cap*.md \
  -o debug.pdf \
  --pdf-engine=pdflatex \
  --toc \
  --number-sections \
  -H ../header.tex \
  --citeproc \
  --bibliography=../refs.bib \
  --csl=../ieee.csl
