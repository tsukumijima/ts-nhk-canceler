
# ts-nhk-canceler

標準入力で与えられた放送波ストリームが NHK の放送であれば処理を打ち切るだけの CLI ツール (ChatGPT で作った試作品) 。

## Build

Windows では別途 gcc と make をインストールする必要があります。

```sh
$ make
$ recpt1 --device /dev/px4video0 BS15_0 - - | ./ts-nhk-canceler 1>/dev/null
```

## License

[MIT License](License.txt)
