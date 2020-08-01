NAME = playground

SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = include/

SRC = main_mesh.cpp \
      ObjLoad.class.cpp \
      Mesh.class.cpp \
      Mat4.class.cpp \
      Vec3.class.cpp \
      VertexBuffer.cpp \
      IndexBuffer.cpp \
      VertexArray.cpp \
      VertexBufferLayout.cpp \
			Shader.cpp \
			Renderer.cpp \
			Texture.cpp \
			Camera.class.cpp \
			stb_image.cpp

OBJ = $(SRC:.cpp=.o)

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))
INCS = $(addprefix -I, $(INC_DIR))

CC = clang++
FLAGS = -std=c++11 -lglfw -lglew -framework OpenGL

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(INCS) $(OBJS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) -std=c++11 $(INCS) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm $(NAME)

re: fclean all
