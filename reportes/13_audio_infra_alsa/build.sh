#!/bin/bash
pandoc \
  --metadata-file=../config.yaml \
  -B Portada_infra_alsa.md \
  inf1*.md \
  -o debug.pdf \
  --pdf-engine=xelatex \
  --toc \
  --number-sections \
  -H ../header.tex \
  --citeproc \
  --bibliography=../refs.bib \
  --csl=../ieee.csl
