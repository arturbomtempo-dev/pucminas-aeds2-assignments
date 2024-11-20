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
 * TP04Q01 - Árvore Binária
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 19/11/2024
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
 * Classe responsável por gerenciar operações relacionadas a objetos do tipo Pokemon.
 * Inclui métodos para criar, ler, buscar e manipular instâncias de Pokemon.
 */
class ManagePokemon {
    private static Pokemon pokemon[] = new Pokemon[801];

    /**
     * Cria uma instância de Pokemon a partir de uma linha de texto formatada.
     * 
     * @param line Linha de texto contendo os dados do Pokémon separados por vírgulas.
     * @return Objeto Pokemon criado a partir dos dados fornecidos.
     */
    public Pokemon createPokemon(String line) {
        Pokemon pokemon = new Pokemon();
        SimpleDateFormat ddf = new SimpleDateFormat("dd/MM/yyyy", Locale.ENGLISH);
        String[] fields = line.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)");
     
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
     * Lê os dados de Pokémon de um arquivo CSV e cria uma lista de objetos Pokemon.
     * 
     * @return Array contendo todas as instâncias de Pokemon lidas do arquivo.
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
     * Busca um Pokémon no array com base no ID fornecido.
     * 
     * @param id Identificador único do Pokémon.
     * @return Objeto Pokemon correspondente ao ID fornecido, ou um objeto vazio caso não encontrado.
     */
    public Pokemon searchPokemon(int id) {
        Pokemon returnedPokemon = new Pokemon();
        int i = 0;

        for (i = 0; i < 801; i++) {
            if (pokemon[i].getId() == id) {
                returnedPokemon = pokemon[i];
            }
        }

        return returnedPokemon;
    }

    /**
     * Troca a posição de dois objetos Pokemon no array.
     * 
     * @param i Índice do primeiro Pokémon.
     * @param j Índice do segundo Pokémon.
     * @return Valor arbitrário, no caso 3, representando o sucesso da operação.
     */
    public int swap(int i, int j) {
        Pokemon temp = pokemon[i];
        pokemon[i] = pokemon[j];
        pokemon[j] = temp; 
        
        return 3;
    }
}

/**
 * Classe responsável por armazenar variáveis globais utilizadas para rastrear
 * o número de comparações e movimentações realizadas em operações diversas.
 */
class GlobalVariables {
    public static int comparisons;
    public static int movements;

    /**
     * Construtor da classe que inicializa as variáveis globais.
     */
    public GlobalVariables(){
        comparisons = 0;
        movements = 0;
    }
}

/**
 * Classe que representa um nó em uma estrutura de árvore binária.
 * Cada nó armazena um objeto do tipo Pokemon e referências para os nós filhos esquerdo e direito.
 */
class Node {
    public Pokemon pokemon;
    public Node left, right;

    /**
     * Construtor que inicializa o nó com um objeto Pokemon, sem filhos.
     * 
     * @param pokemon Objeto Pokemon a ser armazenado no nó.
     */
    public Node(Pokemon pokemon) {
        this(pokemon, null, null);
    }

    /**
     * Construtor que inicializa o nó com um objeto Pokemon e referências para os filhos.
     * 
     * @param pokemon Objeto Pokemon a ser armazenado no nó.
     * @param left Referência para o nó filho à esquerda.
     * @param right Referência para o nó filho à direita.
     */
    public Node(Pokemon pokemon, Node left, Node right) {
        this.pokemon = pokemon;
        this.left = left;
        this.right = right;
    }
}

/**
 * Classe que implementa uma árvore binária para armazenar objetos do tipo Pokemon.
 * Permite a inserção e busca de elementos de forma eficiente.
 */
class BinaryTree {
    private Node root;

    /**
     * Construtor que inicializa a árvore binária vazia.
     */
    public BinaryTree() {
        root = null;
    }

    /**
     * Realiza a busca por um Pokémon na árvore com base no nome.
     * 
     * @param name Nome do Pokémon a ser buscado.
     * @return {@code true} se o Pokémon foi encontrado, {@code false} caso contrário.
     */
    public boolean search(String name) {
        System.out.println(name);
        System.out.print("=>raiz ");
        return search(name, root);
    }

    /**
     * Método auxiliar recursivo para realizar a busca na árvore.
     * 
     * @param name Nome do Pokémon a ser buscado.
     * @param i Referência ao nó atual da árvore.
     * @return {@code true} se o Pokémon foi encontrado, {@code false} caso contrário.
     */
    private boolean search(String name, Node i) {
        boolean found;

        if ( i == null) {
            found = false;
        } else if(name.equals(i.pokemon.getName())) {
            GlobalVariables.comparisons++;
            found = true;
        } else if(name.compareTo(i.pokemon.getName()) < 0) {
            GlobalVariables.comparisons++;
            System.out.print("esq ");
            found = search(name, i.left);
        } else {
            System.out.print("dir ");
            found = search(name, i.right);
        }

        return found;
    }

    /**
     * Insere um Pokémon na árvore binária.
     * 
     * @param pokemon Objeto Pokemon a ser inserido.
     * @throws Exception Caso o Pokémon já exista na árvore.
     */
    public void insert(Pokemon pokemon) throws Exception {
        root = insert(pokemon, root);
    }

    /**
     * Método auxiliar recursivo para inserir um Pokémon na árvore.
     * 
     * @param pokemon Objeto Pokemon a ser inserido.
     * @param i Referência ao nó atual da árvore.
     * @return Referência atualizada do nó após a inserção.
     * @throws Exception Caso o Pokémon já exista na árvore.
     */
    private Node insert(Pokemon pokemon, Node i) throws Exception {
        if (i == null) {
            i = new Node(pokemon);
        } else if (pokemon.getName().compareTo(i.pokemon.getName()) < 0) {
            GlobalVariables.comparisons++;
            i.left = insert(pokemon, i.left);
        } else if (pokemon.getName().compareTo(i.pokemon.getName()) > 0) {
            GlobalVariables.comparisons++;
            i.right = insert(pokemon, i.right);
        } else {
            throw new Exception("Erro ao insert!");
        }

        return i;
    }
}

/**
 * Classe principal que gerencia a execução do programa. 
 * Realiza operações de leitura de entrada, manipulação de árvores binárias e registro de resultados em arquivo.
 */
public class Main {
    /**
     * Salva os resultados da execução em um arquivo especificado.
     * 
     * @param filename Nome do arquivo onde os dados serão salvos.
     * @param comparisons Número total de comparações realizadas durante a execução.
     * @param movements Número total de movimentações realizadas durante a execução.
     * @param endTime Tempo total de execução em milissegundos.
     */
    public static void saveExecutionFile(String filename, int comparisons, int movements, long endTime) {
        try (RandomAccessFile file = new RandomAccessFile(filename, "rw")) {
            file.writeChars("847235" + "\t" +  endTime + "ms" + "\t" + comparisons);
            file.close();
        } catch (IOException err) {
            System.err.println("Erro no arquivo criado: " + err.getMessage());
        }
    }

    /**
     * Verifica se a entrada fornecida corresponde à palavra "FIM".
     * 
     * @param input String de entrada a ser verificada.
     * @return {@code true} se a entrada for "FIM", {@code false} caso contrário.
     */
    public static boolean isEnd(String input) {
        return (input.length() == 3 && input.charAt(0) == 'F' && input.charAt(1) == 'I' && input.charAt(2) == 'M');
    }

    /**
     * Método principal do programa. Lê dados de entrada, insere Pokémon na árvore binária,
     * realiza buscas e salva os resultados em um arquivo.
     * 
     * @param args Argumentos de linha de comando (não utilizados).
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        boolean stop = true;
        ManagePokemon gp = new ManagePokemon();

        gp.readPokemon();

        BinaryTree pokemonTree = new BinaryTree();
        long start = System.currentTimeMillis();
                
        while (stop) {
            String input = sc.nextLine();
            
            if (isEnd(input)) {
                stop = false;
            } else {
                int id = Integer.parseInt(input);

                try {
                    Pokemon pokemon = gp.searchPokemon(id);
                    pokemonTree.insert(pokemon);
                } catch (Exception e){
                    System.out.println("Pokemon não encontrado: " + e.getMessage());
                }
            }
        }

        stop = true;
        
        while (stop) {
            String input = sc.nextLine();
            
            if (isEnd(input)) {
                stop = false;
            } else {
                boolean found = pokemonTree.search(input);
                System.out.println(found ? "SIM" : "NAO");
            }
        }
           
       long endTime = System.currentTimeMillis() - start;

        sc.close();

        saveExecutionFile("847235_arvoreBinaria.txt", GlobalVariables.comparisons, GlobalVariables.movements, endTime);
    }
}