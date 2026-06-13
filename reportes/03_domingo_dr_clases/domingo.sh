#!/bin/bash
pandoc \
  --metadata-file=../config.yaml \
  -B Portada_clases_dr_Domingo.md \
   dom*.md \
  -o clases_Dr_Domingo.pdf \
  --pdf-engine=xelatex \
  --toc \
  --number-sections \
  -H ../header.tex \
  --citeproc \
  --bibliography=../refs.bib \
  --csl=../ieee.csl
