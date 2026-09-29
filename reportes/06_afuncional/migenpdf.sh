pandoc afu1_062_progra_func_norma.md \
  -o 00.pdf \
  --pdf-engine=xelatex \
  -H ../header.tex \
  --citeproc \
  --bibliography=../refs.bib \
  --csl=../ieee.csl \
  --metadata-file=../config.yaml


