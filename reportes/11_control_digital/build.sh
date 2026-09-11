#!/bin/bash
pandoc \
  --metadata-file=../config.yaml \
  -B Portada_clases_ctrl_dig.md \
  cdig*.md \
  -o debug.pdf \
  --pdf-engine=xelatex \
  --toc \
  --number-sections \
  -H ../header.tex \
  --citeproc \
  --bibliography=../refs.bib \
  --csl=../ieee.csl
