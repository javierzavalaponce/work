pandoc Afu2_010_tf_2_ss_python.md \
  -o 00.pdf \
  --pdf-engine=xelatex \
  -H ../header.tex \
  --citeproc \
  --bibliography=../refs.bib \
  --csl=../ieee.csl \
  --metadata-file=../config.yaml


