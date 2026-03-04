pandoc backlog.md -o back.html --standalone --highlight-style=pygments
rsync -aHWP --inplace --delete /home/toto/javi/ /media/toto/KINGSTON/javi/
rsync -avh --exclude='.git/' origen/ destino/
