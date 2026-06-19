#!/bin/bash
pandoc \
  --metadata-file=../config.yaml \
  -B Portada_proyecto.md \
  prj*.md \
  -o out.pdf \
  --pdf-engine=xelatex \
  --toc \
  --number-sections \
  -H ../header.tex \
  --citeproc \
  --bibliography=../refs.bib \
  --csl=../ieee.csl
