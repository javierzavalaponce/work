#!/bin/bash
pandoc \
  --metadata-file=config.yaml \
  -B Portada_julia.md \
  qap8*.md \
  -o julia.pdf \
  --pdf-engine=xelatex \
  --toc \
  --number-sections \
  -H header.tex \
  --citeproc \
  --bibliography=refs.bib \
  --csl=ieee.csl
