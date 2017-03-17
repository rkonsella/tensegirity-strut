  while true ; do
  gatttool --device=D2:B2:10:47:80:83 --char-read --handle 0x0011 -t random | xargs python char_translate.py
done
