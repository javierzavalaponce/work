pandoc Cdig_050_transformada_Z.md \
  -o 00.pdf \
  --pdf-engine=xelatex \
  -H ../header.tex \
  --citeproc \
  --bibliography=../refs.bib \
  --csl=../ieee.csl \
  --metadata-file=../config.yaml


