set nocompatible						"required
filetype off							"required


"set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()


"alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')


"let Vundle manage Vundle, required
Plugin 'gmarik/Vundle.vim'					"Vundle program
Plugin 'tmhedberg/SimplyFold'					"Method & Function folding
Plugin 'vim-scripts/indentpython.vim'				"Auto indent
Plugin 'Valloric/YouCompleteMe'					"Auto Complete
Plugin 'vim-syntastic/syntastic'				"Syntax Checking/Highlighting
Plugin 'scrooloose/nerdtree'					"File tree
Plugin 'jistr/vim-nerdtree-tabs'				"File tree tabs
Plugin 'kien/ctrlp.vim'						"Super Searcher
Plugin 'Lokaltog/powerline', {'rtp': 'powerline/bindings/vim/'}	"Status bar
Plugin 'ryanoasis/vim-devicons'					"Icons for File tree

" add all your plugins here (note older versions of VUndl used Bundle instead of PLugin)

"sp & vs navigation
nnoremap <C-J> <C-W><C-J>
nnoremap <C-K> <C-W><C-K>
nnoremap <C-L> <C-W><C-L>
nnoremap <C-H> <C-W><C-H>


" enable method folding
set foldmethod=indent
set foldlevel=99

" enable folding with the spacebar
nnoremap <space> za

"view the docstrings for folded code
let g:SimpylFold_docstring_preview=1

"indentation after method declerations
au BufNewFile,BufRead *.py
	\set tabstop=4
	\set softtabstop=4
	\set shiftwidth=4
	\set textwidth=79
	\set expandtab
	\set autoindent
	\set fileformat=unix

au BufNewFile,BufREad *.js, *.html, *.css
	\set tabstop=2
	\set softtabstop=2
	\set shiftwidth=2

set encoding=utf-8

"customize AutoComplete
let g:ycm_autoclose_preview_window_after_completion=1
map <leader>g	:YcmCompleter GoToDefinitionElseDecleration<CR>

"make code look pretty
let python_highlight_all=1 
syntax on

"line numbers
set nu

"clipboard access outside vim
set clipboard=unnamedi

"Start NERDtree and leave the cursor in it
autocmd VimEnter * NERDTree 


" All of your Plugins must be added before the following line

call vundle#end()						"required
filetype plugin indent on 					"required				 
