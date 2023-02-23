/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp_make_gen.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:20:01 by dcorenti          #+#    #+#             */
/*   Updated: 2023/02/14 21:10:17 by dcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <string>

bool	is_readable( const std::string & file )  
{  
    std::ifstream fichier( file.c_str() );  
    return !fichier.fail();  
}

void	file_exist(std::string filename)
{
	std::string line;
	int rep;

	rep = 0;
	if (is_readable(filename))
	{
		while (rep == 0)
		{
			std::cout << "\033[1;31m" << filename << " already exist. Do you want delete it for a new " << filename << " ?" << "\033[0m" << std::endl;
			std::cout << "y or n?" << std::endl;
			getline(std::cin, line);
			if (line == "y")
				rep = 1;
			else if (line == "n")
				rep = 2;
			else
				std::cout << "[" << line << "]" << ": Incorrect input.\n" << std::endl;
		}
		if (rep == 2)
		{
			std::cout << "Generation Canceled" << std::endl;
			exit(0);
		}
	}
}

void	write_make_file(std::ofstream& makefile)
{
	makefile << "NAME" << "\t\t\t" << "=" << "\t" << std::endl;
	makefile << "\n";
	makefile << "SRCS" << "\t\t\t" << "=" << "\t" << "main.cpp \\" << std::endl;
	makefile << "\n";
	makefile << "CC" << "\t\t\t\t" << "=" << "\t" << "clang++" << std::endl;
	makefile << "\n";
	makefile << "CPPFLAGS" << "\t\t" << "=" << "\t" << "-Wall -Wextra -Werror -std=c++98" << std::endl;
	makefile << "\n";
	makefile << "RM" << "\t\t\t\t" << "=" << "\t" << "rm -rf" << std::endl;
	makefile << "\n";
	makefile << "OBJS" << "\t\t\t" << "=" << "\t" << "$(SRCS:%.cpp=%.o)" << std::endl;
	makefile << "\n";
	/*---------------------------------------------------------------------------------------------*/
	makefile << "RESET" << "\t\t\t" << "=" << "\t" << "\\033[0m" << std::endl;
	makefile << "GREEN" << "\t\t\t" << "=" << "\t" << "\\033[38;5;46m" << std::endl;
	makefile << "WHITE" << "\t\t\t" << "=" << "\t" << "\\033[38;5;15m" << std::endl;
	makefile << "GREY" << "\t\t\t" << "=" << "\t" << "\\033[38;5;8m" << std::endl;
	makefile << "ORANGE" << "\t\t\t" << "=" << "\t" << "\\033[38;5;202m" << std::endl;
	makefile << "RED" << "\t\t\t\t" << "=" << "\t" << "\\033[38;5;160m" << std::endl;
	makefile << "\n";
	/*---------------------------------------------------------------------------------------------*/
	makefile << "all: $(NAME)" << std::endl;
	makefile << "\n";
	/*---------------------------------------------------------------------------------------------*/
	makefile << "$(NAME): $(OBJS)" << std::endl;
	makefile << "\t" << "$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME) " << std::endl;
	makefile << "\t" << "@echo \"$(GREEN)----------------------------------------------------\"" << std::endl;
	makefile << "\t" << "@echo \"Executable				./$(NAME) $(RESET)\"" << std::endl;
	makefile << "\n";
	/*---------------------------------------------------------------------------------------------*/
	makefile << ".cpp.o:" << std::endl;
	makefile << "\t" << "$(CC) $(CPPFLAGS) -c $< -o $(<:.cpp=.o)" << std::endl;
	makefile << "\n";
	/*---------------------------------------------------------------------------------------------*/
	makefile << "clean:" << std::endl;
	makefile << "\t" << "@echo \"$(RED)----------------------------------------------------\"" << std::endl;
	makefile << "\t" << "$(RM) $(OBJS)" << std::endl;
	makefile << "\t" << "@echo \"REMOVED O-FILES\"" << std::endl;
	makefile << "\t" << "@echo \"----------------------------------------------------$(RESET)\"" << std::endl;
	makefile << "\n";
	/*---------------------------------------------------------------------------------------------*/
	makefile << "fclean: clean" << std::endl;
	makefile << "\t" << "@echo \"$(RED)\"" << std::endl;
	makefile << "\t" << "$(RM) $(NAME)" << std::endl;
	makefile << "\t" << "@echo \"REMOVED EXECUTABLE FILE\"" << std::endl;
	makefile << "\t" << "@echo \"----------------------------------------------------$(RESET)\"" << std::endl;
	makefile << "\n";
	/*---------------------------------------------------------------------------------------------*/
	makefile << "re: fclean all" << std::endl;
	makefile << "\n";
	/*---------------------------------------------------------------------------------------------*/
	makefile << ".PHONY: all clean fclean re" << std::endl;
}

int main(void)
{
	std::string 	filename;
	std::ofstream	makefile;

	filename = "Makefile";
	file_exist(filename);
	makefile.open(filename);
	write_make_file(makefile);
	std::cout << "\033[1;32m" << filename << " created generate with success!\033[0m" << std::endl;
}