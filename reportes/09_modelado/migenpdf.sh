pandoc mod_016_modelado_tarea_Examen_.md \
  -o 00.pdf \
  --pdf-engine=xelatex \
  -H ../header.tex \
  --citeproc \
  --bibliography=../refs.bib \
  --csl=../ieee.csl \
  --metadata-file=../config.yaml


