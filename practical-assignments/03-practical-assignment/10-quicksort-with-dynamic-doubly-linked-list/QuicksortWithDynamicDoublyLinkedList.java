import java.text.SimpleDateFormat;
import java.text.ParseException;
import java.io.RandomAccessFile;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.io.FileReader;
import java.util.Scanner;
import java.util.Arrays;
import java.util.Locale;
import java.util.Date;

/**
 * TP03Q10 - Quicksort com LISTA DINÂMICA DUPLAMENTE ENCADEADA em Java
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 15/11/2024
 */

/**
 * Representa um Pokémon com suas características, incluindo identificação, geração,
 * nome, descrição, tipos, habilidades, peso, altura, taxa de captura, se é lendário e 
 * data de captura.
 */
class Pokemon {
    private int id;
    private int generation;
    private String name;
    private String description;
    private ArrayList<String> types;
    private ArrayList<String> abilities;
    private double weight;
    private double height;
    private int captureRate;
    private boolean isLegendary;
    private Date captureDate;

    /**
     * Construtor padrão para a classe Pokemon.
     * Inicializa todos os atributos com valores padrão.
     */
    public Pokemon() {
        this.id = 0;
        this.generation = 0;
        this.name = "";
        this.description = "";
        this.types = new ArrayList<String>();
        this.abilities = new ArrayList<String>();
        this.weight = 0.0;
        this.height = 0.0;
        this.captureRate = 0;
        this.isLegendary = false;
        this.captureDate = new Date();
    }

    /**
     * Construtor que inicializa um Pokémon com valores específicos.
     * 
     * @param id Identificador único do Pokémon.
     * @param generation Geração à qual o Pokémon pertence.
     * @param name Nome do Pokémon.
     * @param description Descrição breve do Pokémon.
     * @param types Lista de tipos do Pokémon.
     * @param abilities Lista de habilidades do Pokémon.
     * @param weight Peso do Pokémon em quilogramas.
     * @param height Altura do Pokémon em metros.
     * @param captureRate Taxa de captura do Pokémon.
     * @param isLegendary Indica se o Pokémon é lendário.
     * @param captureDate Data de captura do Pokémon.
     */
    public Pokemon(int id, int generation, String name, String description, ArrayList<String> types, ArrayList<String> abilities, double weight, double height, int captureRate, boolean isLegendary, Date captureDate) {
        this.id = id;
        this.generation = generation;
        this.name = name;
        this.description = description;
        this.types = types;
        this.abilities = abilities;
        this.weight = weight;
        this.height = height;
        this.captureRate = captureRate;
        this.isLegendary = isLegendary;
        this.captureDate = captureDate;
    }

    /**
     * Obtém o ID do Pokémon.
     * 
     * @return ID do Pokémon.
     */
    public int getId() {
        return this.id;
    }

    /**
     * Define o ID do Pokémon.
     * 
     * @param id Novo ID do Pokémon.
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * Obtém a geração do Pokémon.
     * 
     * @return Geração do Pokémon.
     */
    public int getGeneration() {
        return this.generation;
    }

    /**
     * Define a geração do Pokémon.
     * 
     * @param generation Nova geração do Pokémon.
     */
    public void setGeneration(int generation) {
        this.generation = generation;
    }

    /**
     * Obtém o nome do Pokémon.
     * 
     * @return Nome do Pokémon.
     */
    public String getName() {
        return this.name;
    }

    /**
     * Define o nome do Pokémon.
     * 
     * @param name Novo nome do Pokémon.
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Obtém a descrição do Pokémon.
     * 
     * @return Descrição do Pokémon.
     */
    public String getDescription() {
        return this.description;
    }

    /**
     * Define a descrição do Pokémon.
     * 
     * @param description Nova descrição do Pokémon.
     */
    public void setDescription(String description) {
        this.description = description;
    }

    /**
     * Obtém a lista de tipos do Pokémon.
     * 
     * @return Lista de tipos do Pokémon.
     */
    public ArrayList<String> getTypes() {
        return this.types;
    }

    /**
     * Define a lista de tipos do Pokémon.
     * 
     * @param types Nova lista de tipos do Pokémon.
     */
    public void setTypes(ArrayList<String> types) {
        this.types = types;
    }

    /**
     * Obtém a lista de habilidades do Pokémon.
     * 
     * @return Lista de habilidades do Pokémon.
     */
    public ArrayList<String> getAbilities() {
        return this.abilities;
    }

    /**
     * Define a lista de habilidades do Pokémon.
     * 
     * @param abilities Nova lista de habilidades do Pokémon.
     */
    public void setAbilities(ArrayList<String> abilities) {
        this.abilities = abilities;
    }

    /**
     * Obtém o peso do Pokémon.
     * 
     * @return Peso do Pokémon.
     */
    public double getWeight() {
        return this.weight;
    }

    /**
     * Define o peso do Pokémon.
     * 
     * @param weight Novo peso do Pokémon.
     */
    public void setWeight(double weight) {
        this.weight = weight;
    }

    /**
     * Obtém a altura do Pokémon.
     * 
     * @return Altura do Pokémon.
     */
    public double getHeight() {
        return this.height;
    }

    /**
     * Define a altura do Pokémon.
     * 
     * @param height Nova altura do Pokémon.
     */
    public void setHeight(double height) {
        this.height = height;
    }

    /**
     * Obtém a taxa de captura do Pokémon.
     * 
     * @return Taxa de captura do Pokémon.
     */
    public int getCaptureRate() {
        return this.captureRate;
    }

    /**
     * Define a taxa de captura do Pokémon.
     * 
     * @param captureRate Nova taxa de captura do Pokémon.
     */
    public void setCaptureRate(int captureRate) {
        this.captureRate = captureRate;
    }

    /**
     * Obtém se o Pokémon é lendário.
     * 
     * @return {@code true} se o Pokémon é lendário; caso contrário, {@code false}.
     */
    public boolean getIsLegendary() {
        return this.isLegendary;
    }

    /**
     * Define se o Pokémon é lendário.
     * 
     * @param isLegendary {@code true} se o Pokémon é lendário; caso contrário, {@code false}.
     */
    public void setIsLegendary(boolean isLegendary) {
        this.isLegendary = isLegendary;
    }

    /**
     * Obtém a data de captura do Pokémon.
     * 
     * @return Data de captura do Pokémon.
     */
    public Date getCaptureDate() {
        return this.captureDate;
    }

    /**
     * Define a data de captura do Pokémon.
     * 
     * @param captureDate Nova data de captura do Pokémon.
     */
    public void setCaptureDate(Date captureDate) {
        this.captureDate = captureDate;
    }
}

/**
 * Classe que representa variáveis globais para armazenar contagens de comparações
 * e movimentações em operações de algoritmos.
 */
class GlobalVariables {
    public static int comparisons;
    public static int movements;

    /**
     * Construtor da classe que inicializa as variáveis globais de contagem de
     * comparações e movimentações com valor 0.
     */
    public GlobalVariables() {
        comparisons = 0;
        movements = 0;
    }

    /**
     * Retorna o número de comparações realizadas.
     *
     * @return Número de comparações realizadas
     */
    public static int getComparisons() {
        return comparisons;
    }

    /**
     * Retorna o número de movimentações realizadas.
     *
     * @return Número de movimentações realizadas
     */
    public static int getMovements() {
        return movements;
    }
}

/**
 * Classe que representa uma célula dupla de uma lista duplamente encadeada,
 * armazenando um objeto { @link Pokemon } e referências para a próxima e a
 * célula anterior.
 */
class DoubleCell {
    public Pokemon pokemon;
    public DoubleCell next, previous;

    /**
     * Construtor padrão que inicializa a célula com valor nulo para o Pokemon.
     */
    public DoubleCell() {
        this(null);
    }

    /**
     * Construtor que inicializa a célula com o objeto Pokemon especificado.
     *
     * @param pokemon Objeto Pokemon a ser armazenado na célula
     */
    public DoubleCell(Pokemon pokemon) {
        this.pokemon = pokemon;
        this.next = null;
    }
}

/**
 * Classe que representa uma lista duplamente encadeada de objetos Pokemon,
 * permitindo inserção e remoção de elementos nas extremidades e ordenação 
 * utilizando o algoritmo Quicksort.
 */
class DoubleList {
    private DoubleCell first, last;
    private int size;

    /**
     * Construtor que inicializa a lista com um nó vazio.
     */
    public DoubleList() {
        first = new DoubleCell();
        last = first;    
    }
    
    /**
     * Retorna o primeiro elemento da lista.
     * 
     * @return Referência para o primeiro elemento da lista
     */
    public DoubleCell getFirst(){
        return this.first;
    }

    /**
     * Retorna o último elemento da lista.
     * 
     * @return Referência para o último elemento da lista
     */
    public DoubleCell getLast(){
        return this.last;
    }
 
    /**
     * Retorna o tamanho atual da lista.
     * 
     * @return Número de elementos na lista
     */
    public int getSize() {
        return size;
    }

    /**
     * Insere um novo Pokemon no final da lista.
     * 
     * @param pokemon Objeto Pokemon a ser inserido
     */
    public void insertEnd(Pokemon pokemon) {
        last.next = new DoubleCell(pokemon);
        last.next.previous = last;
        last = last.next;
        size++;
    }

    /**
     * Remove e retorna o primeiro Pokemon da lista.
     * 
     * @return Objeto Pokemon removido
     * @throws Exception Se a lista estiver vazia
     */
    public Pokemon removeStart() throws Exception {
        if (first == last){
            throw new Exception("Erro ao remover elemento no início da lista.");
        }

        DoubleCell temp = first;
        first = first.next;
        Pokemon response = first.pokemon;
        temp.next = first.previous = null;
        temp = null;
        size--;

        return response;
    }

    /**
     * Remove e retorna o último Pokemon da lista.
     * 
     * @return Objeto Pokemon removido
     * @throws Exception Se a lista estiver vazia
     */
    public Pokemon removeEnd() throws Exception {
        if (first == last) {
            throw new Exception("Erro ao remover elemento da lista.");
        }

        Pokemon response = last.pokemon;
        last = last.previous;
        last.next.previous = null;
        last.next = null;
        size--;

        return response;
    }

    /**
     * Exibe os elementos da lista no formato definido.
     */
	public void show() {
		show(first.next, 0);
	}
    
    /**
     * Método auxiliar recursivo para exibir os elementos da lista.
     * 
     * @param i Célula atual sendo exibida
     * @param count Contador para auxiliar na exibição recursiva
     */
    private void show(DoubleCell i, int count) {
        if (i != null) {
            SimpleDateFormat outputDateFormat = new SimpleDateFormat("dd/MM/yyyy");
            String formattedDate = outputDateFormat.format(i.pokemon.getCaptureDate());

            System.out.println("[#"
                                + i.pokemon.getId() + " -> "
                                + i.pokemon.getName() + ": "
                                + i.pokemon.getDescription() + " - "
                                + i.pokemon.getTypes() + " - "
                                + i.pokemon.getAbilities() + " - "
                                + i.pokemon.getWeight() + "kg - "
                                + i.pokemon.getHeight() + "m - "
                                + i.pokemon.getCaptureRate() + "% - "
                                + i.pokemon.getIsLegendary() + " - "
                                + i.pokemon.getGeneration() + " gen] - "
                                + formattedDate 
                            );

            show(i.next, ++count);
        }
    }

    /**
     * Obtém o elemento pivô na posição especificada.
     * 
     * @param position Posição do pivô desejado
     * @param list Lista de onde o pivô será retirado
     * @return Célula na posição especificada
     */
    private DoubleCell getPivot(int position, DoubleList list) {
        DoubleCell current = list.first.next;

        for (int i = 0; i < position && current != null; i++) {
            current = current.next;
        }

        return current; 
    }

    /**
     * Troca o conteúdo entre duas células na lista.
     * 
     * @param ci Primeira célula a ser trocada
     * @param cj Segunda célula a ser trocada
     */
    public void swap(DoubleCell ci, DoubleCell cj) {
        Pokemon temp = ci.pokemon;
        ci.pokemon = cj.pokemon;
        cj.pokemon = temp;
    }

    /**
     * Método de ordenação da lista usando o algoritmo Quicksort.
     * 
     * @param list Lista a ser ordenada
     * @param left Índice inicial do intervalo
     * @param right Índice final do intervalo
     * @param cLeft Célula inicial do intervalo
     * @param cRight Célula final do intervalo
     */
    public void quicksort(DoubleList list, int left, int right, DoubleCell cLeft, DoubleCell cRight) {
        DoubleCell ci = cLeft, cj = cRight;
        DoubleCell pivot = getPivot(left, list);
        int i = left, j = right;
        
        while (i <= j) {
            while (ci.pokemon.getGeneration() < pivot.pokemon.getGeneration() || (ci.pokemon.getGeneration() == pivot.pokemon.getGeneration() && ci.pokemon.getName().compareTo(pivot.pokemon.getName()) < 0)) {
                GlobalVariables.comparisons++;
                i++;
                ci = ci.next;
            }
    
            while (cj.pokemon.getGeneration() > pivot.pokemon.getGeneration() || (cj.pokemon.getGeneration() == pivot.pokemon.getGeneration() && cj.pokemon.getName().compareTo(pivot.pokemon.getName()) > 0)) {
                GlobalVariables.comparisons++;
                j--;
                cj = cj.previous;
            }
    
            if (i <= j) {
                GlobalVariables.movements += 3;
                swap(ci, cj);
                ci = ci.next;
                cj = cj.previous;
                i++;
                j--;
            }
        }
    
        if (left < j) {
            quicksort(list, left, j, cLeft, cj);
        }

        if (i < right) {
            quicksort(list, i, right, ci, cRight);
        }
    }
}

/**
 * Classe responsável por gerenciar objetos Pokemon, realizando a criação,
 * leitura de dados de arquivo e busca de Pokemon por ID.
 */
class ManagePokemon {
    private static Pokemon pokemon[] = new Pokemon[801];

    /**
     * Cria um objeto Pokemon a partir de uma linha de texto.
     * 
     * @param row Linha de texto contendo dados do Pokemon separados por vírgulas
     * @return Objeto Pokemon com os atributos preenchidos
     */
    public Pokemon createPokemon(String row) {
        Pokemon pokemon = new Pokemon();
        SimpleDateFormat ddf = new SimpleDateFormat("dd/MM/yyyy", Locale.ENGLISH); 
        String[] fields = row.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)");
        
        pokemon.setId(Integer.parseInt(fields[0])); 
        pokemon.setGeneration(Integer.parseInt(fields[1])); 
        pokemon.setName(fields[2]); 
        pokemon.setDescription(fields[3]); 
                
        ArrayList<String> types = new ArrayList<>();

        types.add("'" + fields[4] + "'");

        if (!fields[5].isEmpty()) {
            types.add("'" + fields[5] + "'");
        }

        pokemon.setTypes(types); 

        pokemon.getAbilities().addAll(
            Arrays.asList(
                fields[6]
                .replace("\"", "")
                .replace("[", "")
                .replace("]", "")
                .split(", ")
            )
        );
                                        
        pokemon.setWeight(fields[7].isEmpty() ? 0.0 : Double.parseDouble(fields[7])); 
        pokemon.setHeight(fields[8].isEmpty() ? 0.0 : Double.parseDouble(fields[8]));         
        pokemon.setCaptureRate(Integer.parseInt(fields[9])); 
        pokemon.setIsLegendary(fields[10].equals("1")); 
        
        try {
            pokemon.setCaptureDate(ddf.parse(fields[11]));
        } catch (ParseException e) {
            e.printStackTrace();
        }
        
        return pokemon;
    }
    
    /**
     * Lê dados de Pokemon de um arquivo CSV e preenche o array pokemon.
     * 
     * @return Array de objetos Pokemon com os dados do arquivo
     */
    public Pokemon[] readPokemon() {
        int i = 0;
 
        try (BufferedReader br = new BufferedReader(new FileReader("/tmp/pokemon.csv"))) {
            String line = br.readLine();
 
            line = br.readLine();
 
            while (line != null) {
                pokemon[i++] =  createPokemon(line);
                line = br.readLine();
            }
        } catch (IOException e) {
            System.out.println("Erro ao ler o arquivo: " + e.getMessage());
        }
 
        return pokemon;
    }

    /**
     * Busca um Pokemon pelo ID no array pokemon.
     * 
     * @param id Identificador do Pokemon
     * @return Objeto Pokemon correspondente ao ID, ou um objeto vazio se não encontrado
     */
    public Pokemon searchPokemon(int id) {
        int i = 0;

        Pokemon returnedPokemon = new Pokemon();

        for (i = 0; i < 801; i++) {
            if (pokemon[i].getId() == id) {
                returnedPokemon = pokemon[i];
            }
        }

        return returnedPokemon;
    }
}

/**
 * Classe que implementa a execução de uma ordenação Quicksort em uma lista
 * duplamente encadeada dinâmica de objetos Pokemon e salva as estatísticas de execução.
 */
public class QuicksortWithDynamicDoublyLinkedList {
    /**
     * Salva as estatísticas de execução em um arquivo.
     * 
     * @param filename Nome do arquivo onde os dados serão salvos
     * @param comparisons Número de comparações realizadas na ordenação
     * @param movements Número de movimentos realizados na ordenação
     * @param endTime Tempo total de execução em milissegundos
     */
    public static void saveExecutionFile(String filename, int comparisons, int movements, long endTime) {
        try (RandomAccessFile file = new RandomAccessFile(filename, "rw")) {
            file.writeChars("847235\t"+ comparisons + "\t" + movements + "\t" + endTime +"ms");
            file.close();
        } catch(IOException err) {
            System.err.println("Erro no arquivo criado: " + err.getMessage());
        }
    }

    /**
     * Verifica se a entrada indica o final do programa.
     * 
     * @param input Entrada a ser verificada
     * @return true se a entrada for "FIM", false caso contrário
     */
    public static boolean isEnd(String input){
        return (input.length() == 3 && input.charAt(0) == 'F' && input.charAt(1) == 'I' && input.charAt(2) == 'M');
    }

    /**
     * Método principal do programa, responsável por ler os dados de entrada,
     * ordenar os Pokemon e salvar as estatísticas.
     * 
     * @param args Argumentos de linha de comando (não utilizados)
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        boolean stop = true;
        int i = 0;
        
        ManagePokemon mp = new ManagePokemon();

        mp.readPokemon();

        DoubleList pokemonsList = new DoubleList();
                
        while (stop) {
            String input = sc.nextLine();

            if (isEnd(input)) {
                stop = false;
            } else {
                try {
                    int id = Integer.parseInt(input.trim());
                    Pokemon pokemon = mp.searchPokemon(id);
                    pokemonsList.insertEnd(pokemon);
                    i++;
                } catch (NumberFormatException e) {
                    System.out.println("Entrada inválida. Por favor, insira um número inteiro.");
                } catch (Exception e) {
                    System.out.println("Pokemon não encontrado: " + e.getMessage());
                }
            }
        }

        long start = System.currentTimeMillis();

        pokemonsList.quicksort(pokemonsList, 0, pokemonsList.getSize() - 1, pokemonsList.getFirst().next, pokemonsList.getLast());

        long endTime = System.currentTimeMillis() - start;

        pokemonsList.show();

        sc.close();

        saveExecutionFile("847235_quicksort3.txt", GlobalVariables.getComparisons(), GlobalVariables.getMovements(), endTime);
    }
}