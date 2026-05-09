#!/bin/bash
pandoc \
  --metadata-file=config.yaml \
  -B portada.md \
  cap*.md \
  -o resultado.pdf \
  --pdf-engine=xelatex \
  --toc \
  --number-sections \
  -H header.tex \
  --citeproc \
  --bibliography=refs.bib \
  --csl=ieee.csl
