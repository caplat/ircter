NAME = ircserv

SRCS = main.cpp \
Channel.cpp \
ChannelMode.cpp \
Nick.cpp \
Privmsg.cpp \
Server.cpp \
User.cpp \
utilsTosend.cpp \

CXX = c++

MY_OBJECTS = $(SRCS:.cpp=.o)

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $(<:.cpp=.o)

$(NAME): $(MY_OBJECTS)
	$(CXX) $(CXXFLAGS) $(MY_OBJECTS) -o $(NAME)

RM = rm -f

clean:
	$(RM) $(MY_OBJECTS)

fclean: clean
	${RM} ${NAME}

re:	fclean all