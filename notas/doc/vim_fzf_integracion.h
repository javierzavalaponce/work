sudo apt install ripgrep
sudo apt install fzf

curl -fLo ~/.vim/autoload/plug.vim --create-dirs https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim

cat .vimrc 
" Inicializar vim-plug
call plug#begin('~/.vim/plugged')

" Plugins a instalar (SOLO dentro del bloque begin/end)
Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
Plug 'junegunn/fzf.vim'

" Finalizar vim-plug
call plug#end()

" Configuración opcional de fzf
set rtp+=/usr/local/opt/fzf

" Atajo de teclado para abrir fzf en Vim (Ctrl+P)
nnoremap <C-p> :Files<CR>
nnoremap <C-g> :Rg<CR>
nnoremap <C-b> :Buffers<CR>
nnoremap <C-l> :Lines<CR>


" Usar fd (más rápido que find) - instala primero: sudo apt install fd-find
let $FZF_DEFAULT_COMMAND = 'fd --type f --hidden --follow --exclude .git'




Esto es lo que tenia antes de este  cambio (hoy junio 9):

nnoremap <C-Down> :m .+1<CR>
nnoremap <C-Up> :m .-2<CR>

vnoremap <C-Down> :m '>+1<CR>gv=gv
vnoremap <C-Up> :m '<-2<CR>gv=gv
