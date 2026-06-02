FROM gcc:latest

WORKDIR /app

COPY . .

RUN gcc main.c data_structures.c dom_parser.c dom_operations.c hash_table.c -o dom_editor

CMD ["./dom_editor"]