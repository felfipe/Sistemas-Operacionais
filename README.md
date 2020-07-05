# Sistemas-Operacionais
Trabalhos realizados para a disciplina de Sistemas Operacionais

Trabalho 1:
O primeiro trabalho consiste em apresentar algumas chamadas de sistemas básicas de um sistema Unix, bem como mostrar suas aplicações, analisando suas chamadas através de ferramentas como strace e time. Além disso, foram apresentados os conceitos de processos cpu_bound e IO_boud, com exemplos de códigos de cada um deles.

Trabalho 2:
O segundo trabalho consiste em apresentar um famoso problema de sincronização: problema do produtor e consumidor. Neste trabalho, apresentamos o problema junto com sua solução que adotamos: o uso de semáforos e primitivas de sleep/wakeup.

Trabalho 3:
O terceiro trabalho consiste em apresentar um simulador de memória virtual. No simulador, podemos instanciar processos, memória primária e secundária e tabela de páginas. Os processos possuem um espaço de endereçamento virtual que pode ser traduzido para um endereço real na memória principal através da tabela de páginas. Quando a página referenciada não está na memória principal, o simulador traz a memória em disco para a memória principal, adotando uma política de substituição (LRU ou relógio) que pode ser definida pelo usuário. Parâmetros como tamanho de página, tamanho da memória principal e o tamanho da memória secundária também podem ser definidos pelo usuário.
