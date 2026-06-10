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



----------------------
Esta es la version que me quedo en equipo del lab
------

toto@192:~$ cat .vimrc
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

" Alias: mm = marks
cnoreabbrev mm marks

" ============================================
" FUNCIÓN DEFINITIVA: MUESTRA CONTEXTO DE TODAS LAS MARCAS
" ============================================
function! FzfMarks()
  " Obtener todas las marcas
  let all_marks = getmarklist()

  if empty(all_marks)
    echo "No hay marcas. Usa ma, mA, etc."
    return
  endif

  let items = []

  for mark_info in all_marks
    " Obtener datos de la marca
    let mark_char = mark_info.mark
    let file_path = mark_info.file
    let pos = mark_info.pos
    let line_num = pos[1]  " El número de línea está en el índice 1

    " Limpiar el carácter de la marca (quitar comillas simples)
    let mark_char = substitute(mark_char, "^'", "", "")

    " Leer el contenido de la línea del archivo correspondiente
    let content = ""
    let file_short = fnamemodify(file_path, ':t')

    try
      " Leer el archivo y obtener la línea específica
      let file_lines = readfile(expand(file_path))
      if line_num <= len(file_lines)
        let content = file_lines[line_num - 1]
        " Limpiar y acortar el contenido
        let content = substitute(content, '^\s\+', '', '')
        if len(content) > 60
          let content = content[:57] . '...'
        endif
      else
        let content = "(línea fuera de rango)"
      endif
    catch
      let content = "(no se pudo leer el archivo)"
    endtry

    " Si no hay contenido, mostrar el nombre del archivo
    if content == ""
      let content = "[📁 " . file_short . "]"
    else
      let content = "[" . file_short . "] " . content
    endif

    " Agregar a la lista (formato bonito)
    call add(items, printf("%-2s │ %4d │ %s", mark_char, line_num, content))
  endfor

  " Ordenar por nombre de marca para mejor visualización
  call sort(items)

  " Mostrar en fzf
  call fzf#run({
        \ 'source': items,
        \ 'sink': { selected -> s:JumpToMark(selected, all_marks) },
        \ 'options': '--prompt="📌 Marcas> " --with-nth=1,2,3 --delimiter="│" --height=60% --layout=reverse'
        \ })
endfunction

" Función auxiliar para saltar a la marca seleccionada
function! s:JumpToMark(selected, all_marks)
  let mark_char = trim(split(a:selected, '│')[0])

  " Buscar la marca en la lista
  for mark_info in a:all_marks
    let current_mark = substitute(mark_info.mark, "^'", "", "")
    if current_mark == mark_char
      " Saltar al archivo y línea
      execute "edit " . expand(mark_info.file)
      execute "normal! " . mark_info.pos[1] . "G"
      execute "normal! " . mark_info.pos[2] . "|"
      break
    endif
  endfor
endfunction

" Comandos
command! FzfMarks call FzfMarks()
cnoreabbrev fm FzfMarks




