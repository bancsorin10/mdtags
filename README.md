

# mdtags for vim

+ generate tags for `.md` files to be used similarly to obsidian note taking
  app, in order to be used in vim

+ generates a tag for each file in the current directory, and for each header
  in each file

+ in order to use the tags, I added the following vim setting that will remap
  the jump to tag:

```
noremap <silent> <C-]> "l2ya[:exec("tag ".@l)<cr>
```

+ for convenience I also have `Lexplore` set up for this environment:

```
noremap <silent> <f3> :Lex<cr> :vert resize 30<cr>
```

+ possible future improvements:
  - support for back links which would likely be using vimgrep to search for
    certain tags
