alias ll='ls -alF'
alias la='ls -A'

PROMPT_COMMAND=__prompt_command # Func to gen PS1 after CMDs

__prompt_command() {
    local EXIT="$?"             # This needs to be first
    PS1=""

    local RCol='\[\e[0m\]'

    local Red='\[\e[0;31m\]'
    local Gre='\[\e[0;32m\]'
    local BYel='\[\e[1;33m\]'
    local BBlu='\[\e[1;34m\]'
    local Pur='\[\e[0;35m\]'

    PS1+="$EXIT|"
    if [ $EXIT != 0 ]; then
        PS1+="${Red}\u${RCol}"      # Add red if exit code non 0
    else
        PS1+="${Gre}\u${RCol}"
    fi

    PS1+="${RCol}@${BBlu}\h ${Pur}\W${BYel}$ ${RCol}"
}

fortune

## it is up to PC
# export GOPATH=$(go env GOPATH)
# PATH=$HOME'/bin/node-v8.12.0-linux-x64/bin:'$PATH
# PATH=$HOME'/bin/idea-IC-182.4892.20/bin:'$PATH
# PATH=$HOME'/.local/bin:'$PATH
# PATH=$GOPATH'/bin:'$PATH
# PATH=$HOME'/VM/android-studio/bin:'$PATH
# PATH=$HOME'/bin:'$PATH

