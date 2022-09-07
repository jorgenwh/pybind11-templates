if [ ! -d temp/ ]; then
  mkdir temp
fi

cd temp && cmake .. && make && cd ..
printf -- "----- PROGRAM OUTPUT -----\n"
python main.py
