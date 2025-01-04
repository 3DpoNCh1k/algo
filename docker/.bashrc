export ALGO_PATH=/algo

# don't put duplicate lines or lines starting with space in the history.
# See bash(1) for more options
HISTCONTROL=ignoreboth

# append to the history file, don't overwrite it
shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

alias ls='ls --color=auto'
alias l='ls -CFG'
alias la='ls -AFG'
alias ll='ls -alFG'

PS1="\e[0;32m\u@\h\e[m:\w\n$ "

if [ -f /etc/bash_completion ]; then
  . /etc/bash_completion
fi

cd $ALGO_PATH
