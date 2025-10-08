/*
 * -------------------------------------------
 *  ПРАКТИЧЕСКАЯ РАБОТА №3
 *  ФАЙЛ: process.c
 *  НАЗНАЧЕНИЕ: Чтение файла, созданного родительским процессом
 *  -------------------------------------------
 *  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
	    printf("[process] Дочерний процесс запущен\n");
	        
	        int fd = open("output.txt", O_RDONLY);
		    if (fd == -1) {
			            perror("[process] Ошибка открытия файла");
				            return 1;
					        }
		        
		        printf("[process] Содержимое файла output.txt:\n");
			    printf("----------------------------------------\n");
			        
			        char buffer[256];
				    ssize_t bytes_read;
				        
				        while ((bytes_read = read(fd, buffer, sizeof(buffer)-1)) > 0) {
						        buffer[bytes_read] = '\0';
							        printf("%s", buffer);
								    }
					    
					    printf("----------------------------------------\n");
					        printf("[process] Файл прочитан успешно\n");
						    
						    close(fd);
						        return 0;
} 
