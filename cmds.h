pandoc backlog.md -o back.html --standalone --highlight-style=pygments
rsync -aHWP --inplace --delete /home/toto/javi/ /media/toto/KINGSTON/javi/
rsync -avh --exclude='.git/' origen/ destino/

pdftk zill.pdf cat 17-25 output salida.pdf



rsync -avh --progress /home/toto/doc/ /media/toto/WORK_ND_DOC/doc/
