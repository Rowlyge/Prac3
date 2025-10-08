/*
 * -------------------------------------------
 *  ПРАКТИЧЕСКАЯ РАБОТА №3
 *  ПРОГРАММА: File Redirect
 *  ФАЙЛ: prog1.c
 *  НАЗНАЧЕНИЕ: Перенаправление вывода с dup2() и работа с файлами
 *  -------------------------------------------
 *  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

void redirect_to_file() {
	    int fd, saved_stdout;
	        
	        printf("[prog1] Открываем файл для записи...\n");
		    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		        if (fd == -1) {
				        perror("[prog1] Ошибка открытия файла");
					        exit(1);
						    }
			    
			    printf("[prog1] Сохраняем оригинальный stdout...\n");
			        saved_stdout = dup(STDOUT_FILENO);
				    
				    printf("[prog1] Перенаправляем stdout в файл...\n");
				        if (dup2(fd, STDOUT_FILENO) == -1) {
						        perror("[prog1] Ошибка dup2");
							        close(fd);
								        exit(1);
									    }
					    
					    printf("=== ДАННЫЕ ЗАПИСАННЫЕ В ФАЙЛ ===\n");
					        printf("Время создания: %ld\n", time(NULL));
						    printf("Этот текст записан через перенаправленный stdout\n");
						        
						        for(int i = 1; i <= 5; i++) {
								        printf("Строка %d: Hello from redirected output!\n", i);
									    }
							    
							    printf("=== КОНЕЦ ДАННЫХ ===\n");
							        
							        fflush(stdout);
								    dup2(saved_stdout, STDOUT_FILENO);
								        
								        printf("[prog1] Вывод восстановлен на экран!\n");
									    
									    close(fd);
									        close(saved_stdout);
}

int main() {
	    printf("=== НАЧАЛО РАБОТЫ ПРОГРАММЫ ===\n");
	        
	        redirect_to_file();
		    
		    printf("[prog1] Запускаем дочерний процесс для чтения файла...\n");
		        
		        pid_t pid = fork();
			    if (pid == 0) {
				            execl("./process", "process", NULL);
					            perror("[prog1] Ошибка exec");
						            exit(1);
							        } else if (pid > 0) {
									        wait(NULL);
										        printf("[prog1] Дочерний процесс завершил работу\n");
											    } else {
												            perror("[prog1] Ошибка fork");
													            exit(1);
														        }
			        
			        printf("=== ПРОГРАММА ЗАВЕРШЕНА ===\n");
				    return 0;
} 
