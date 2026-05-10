#!/bin/bash
pandoc \
  --metadata-file=config.yaml \
  -B Portada_clases_basilio.md \
  cap5*.md \
  -o basilio.pdf \
  --pdf-engine=xelatex \
  --toc \
  --number-sections \
  -H header.tex \
  --citeproc \
  --bibliography=refs.bib \
  --csl=ieee.csl
