# Markdown to latex Regular Expressions for global substitution

**Note:** Also checkout the [pandoc](https://pandoc.org/).

```regex
!\[.*\]\((.*)\)
\\includegraphics[width=\\textwidth]{$1}
```

```regex
`([^`]+)`
\\texttt{$1}
```

```regex
\*\b(.*)\b\*
\\textit{$1}
```

```regex
\[(.*)\]\((.*)\)
\\href{$2}{$1}
```
