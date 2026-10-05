pandoc mod_015_modelado_sist_mec_ej5.md \
  -o 00.pdf \
  --pdf-engine=xelatex \
  -H ../header.tex \
  --citeproc \
  --bibliography=../refs.bib \
  --csl=../ieee.csl \
  --metadata-file=../config.yaml


