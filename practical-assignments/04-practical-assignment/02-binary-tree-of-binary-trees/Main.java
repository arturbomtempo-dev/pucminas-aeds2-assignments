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
 * TP04Q02 - Árvore Binária de Árvore Binárias
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 26/11/2024
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
    public GlobalVariables() {
        comparisons = 0;
        movements = 0;
    }
}

/**
 * Classe que representa um nó em uma estrutura de árvore binária.
 * Cada nó pode armazenar um elemento do tipo inteiro, referências para os nós filhos esquerdo e direito,
 * além de uma referência para um nó adicional do tipo Node2.
 */
class Node {
    public int element;
    public Node left, right;
    public Node2 other;

    /**
     * Construtor que inicializa o nó com um elemento e define os filhos e o nó adicional como nulos.
     * 
     * @param element Elemento do tipo inteiro a ser armazenado no nó.
     */
    public Node(int element) {
        this.element = element;
        this.left = this.right = null;
        this.other = null;
    }

    /**
     * Construtor que inicializa o nó com um elemento e referências específicas para os nós filhos.
     * 
     * @param element Elemento do tipo inteiro a ser armazenado no nó.
     * @param left Referência para o nó filho à esquerda.
     * @param right Referência para o nó filho à direita.
     */
    public Node(int element, Node left, Node right) {
        this.element = element;
        this.left = left;
        this.right = right;
    }
}

/**
 * Classe que representa um nó em uma estrutura de árvore binária específica para armazenar objetos do tipo Pokemon.
 * Cada nó armazena um objeto Pokemon e referências para os nós filhos esquerdo e direito.
 */
class Node2 {
    public Pokemon pokemon;
    public Node2 left, right;

    /**
     * Construtor que inicializa o nó com um objeto Pokemon e define os filhos como nulos.
     * 
     * @param pokemon Objeto Pokemon a ser armazenado no nó.
     */
    public Node2(Pokemon pokemon) {
        this.pokemon = pokemon;
        this.left = this.right = null;
    }

    /**
     * Construtor que inicializa o nó com um objeto Pokemon e referências específicas para os nós filhos.
     * 
     * @param pokemon Objeto Pokemon a ser armazenado no nó.
     * @param left Referência para o nó filho à esquerda.
     * @param right Referência para o nó filho à direita.
     */
    public Node2(Pokemon Pokemon, Node2 left, Node2 right) {
        this.pokemon = pokemon;
        this.left = left;
        this.right = right;
    }
}

/**
 * Classe que representa uma árvore binária de árvores binárias.
 * A árvore principal organiza os elementos baseados no valor do restante da divisão do índice de captura por 15.
 * Cada nó da árvore principal pode conter outra árvore binária que organiza os objetos do tipo Pokemon por nome.
 */
class BinaryTreeBinaryTrees {
    private Node root;

    /**
     * Construtor padrão que inicializa a árvore principal e insere valores predefinidos.
     * Os valores inseridos configuram a estrutura básica da árvore principal.
     */
    public BinaryTreeBinaryTrees() {
        root = null;

        try {
            insert(7); 
            insert(3);
            insert(11);
            insert(1);
            insert(5);
            insert(9);
            insert(13);
            insert(0);
            insert(2);
            insert(4);
            insert(6);
            insert(8);
            insert(10);
            insert(12);
            insert(14);
        } catch(Exception e) {
            System.err.println("Erro ao configurar a árvore de árvore: " + e.getMessage());
        }
    }

    /**
     * Insere um elemento na árvore principal.
     * 
     * @param element Elemento a ser inserido.
     * @throws Exception Caso o elemento já exista na árvore.
     */
    public void insert(int element) throws Exception {
        root = insert(element, root);
    }

    /**
     * Método auxiliar para inserir um elemento na árvore principal recursivamente.
     * 
     * @param element Elemento a ser inserido.
     * @param i Nó atual da árvore.
     * @return Nó atualizado após a inserção.
     * @throws Exception Caso o elemento já exista na árvore.
     */
    private Node insert(int element, Node i) throws Exception {
        if (i == null) {
            i = new Node(element);
        } else if (element < i.element) {
            GlobalVariables.comparisons++;
            i.left = insert(element, i.left);
        } else if (element > i.element) {
            GlobalVariables.comparisons++;
            i.right = insert(element, i.right);
        } else {
            throw new Exception("Erro ao insert! elemento inexistente");
        }

        return i;
    }

    /**
     * Insere um objeto Pokemon na árvore binária de árvores.
     * 
     * @param pokemon Objeto Pokemon a ser inserido.
     * @throws Exception Caso o nó da árvore principal correspondente ao índice de captura não exista.
     */
    public void insert(Pokemon pokemon) throws Exception {
        insert(pokemon, root);
    }

    /**
     * Método auxiliar para inserir um objeto Pokemon na árvore binária de árvores.
     * 
     * @param pokemon Objeto Pokemon a ser inserido.
     * @param i Nó atual da árvore principal.
     * @return Nó atualizado após a inserção.
     * @throws Exception Caso o nó correspondente não exista ou algum erro ocorra durante a inserção.
     */
    private Node insert(Pokemon pokemon, Node i) throws Exception {
        if (i == null) {
            throw new Exception("Erro ao inserir: elemento inválido.");
        } else if (pokemon.getCaptureRate() % 15 < i.element) {
            GlobalVariables.comparisons++;
            i.left = insert(pokemon, i.left);
        } else if (pokemon.getCaptureRate() % 15 > i.element) {
            GlobalVariables.comparisons++;
            i.right = insert(pokemon, i.right);
        } else {
            i.other = insert(pokemon, i.other);
        }
        
        return i;
    }

    /**
     * Insere um objeto Pokemon na árvore secundária dentro de um nó da árvore principal.
     * 
     * @param pokemon Objeto Pokemon a ser inserido.
     * @param i Nó atual da árvore secundária.
     * @return Nó atualizado após a inserção.
     * @throws Exception Caso o Pokémon já exista na árvore secundária.
     */
    private Node2 insert(Pokemon pokemon, Node2 i) throws Exception {
        if (i == null) {
            i = new Node2(pokemon);
        } else if (pokemon.getName().compareTo(i.pokemon.getName()) < 0) {
            GlobalVariables.comparisons++;
            i.left = insert(pokemon, i.left);
        } else if (pokemon.getName().compareTo(i.pokemon.getName()) > 0) {
            GlobalVariables.comparisons++;
            i.right = insert(pokemon, i.right);
        } else {
            throw new Exception("Erro ao inserir. Elemento inexistente.");
        }

        return i;
    }

    /**
     * Realiza uma busca por um Pokémon pelo nome na árvore binária de árvores.
     * 
     * @param name Nome do Pokémon a ser buscado.
     * @return {@code true} se o Pokémon for encontrado, caso contrário, {@code false}.
     */
    public boolean search(String name) {
        System.out.println("=> " + name);
        System.out.print("raiz ");
        return walkPre(name, root);
    }

    /**
     * Método auxiliar para percorrer a árvore principal em pré-ordem durante a busca.
     * 
     * @param name Nome do Pokémon a ser buscado.
     * @param i Nó atual da árvore principal.
     * @return {@code true} se o Pokémon for encontrado, caso contrário, {@code false}.
     */
    private boolean walkPre(String name, Node i) {
        boolean found;

        if (i == null) {
            found = false;
        } else {
			found = search(name, i.other);
            
            if (found == false) {
                System.out.print(" ESQ ");
                found = walkPre(name, i.left);
            }

            if (found == false) {
                System.out.print(" DIR ");
                found = walkPre(name, i.right);
            }
        }

        return found;
    }

    /**
     * Método auxiliar para buscar um Pokémon pelo nome em uma árvore secundária.
     * 
     * @param name Nome do Pokémon a ser buscado.
     * @param i Nó atual da árvore secundária.
     * @return {@code true} se o Pokémon for encontrado, caso contrário, {@code false}.
     */
    private boolean search(String name, Node2 i) {
        boolean found;

        if (i == null) {
            found = false;
        } else if (name.equals(i.pokemon.getName())) {
            GlobalVariables.comparisons++;
            found = true;
        } else if (name.compareTo(i.pokemon.getName()) < 0) {
            GlobalVariables.comparisons++;
            System.out.print("esq ");
            found = search(name, i.left);
        } else {
            System.out.print("dir ");
            found = search(name, i.right);
        }

        return found;
    }
}

/**
 * Classe principal que gerencia a execução do programa.
 * Contém métodos auxiliares para salvar resultados e verificar condições de encerramento,
 * além do método principal `main` que coordena as operações da aplicação.
 */
public class Main {
    /**
     * Salva em um arquivo os resultados da execução, incluindo comparações, movimentos e tempo de execução.
     * 
     * @param filename Nome do arquivo onde os resultados serão salvos.
     * @param comparisons Número de comparações realizadas durante a execução.
     * @param movements Número de movimentos realizados durante a execução.
     * @param endTime Tempo total de execução em milissegundos.
     */
    public static void saveExecutionFile(String filename, int comparisons, int movements, long endTime) {
        try (RandomAccessFile file = new RandomAccessFile(filename, "rw")) {
            file.writeChars("847235" + "\t" +  endTime + "ms" + "\t" + comparisons);
            file.close();
        } catch(IOException err) {
            System.err.println("Erro Node arquivo criado: " + err.getMessage());
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
     * Método principal que coordena a execução do programa.
     * 
     * Lê os dados de entrada, insere Pokémon em uma árvore de árvores e realiza buscas.
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        boolean stop = true;
        
        ManagePokemon gp = new ManagePokemon();

        gp.readPokemon();

        BinaryTreeBinaryTrees pokemonTree = new BinaryTreeBinaryTrees();
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
                } catch(Exception e) {
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
                System.out.println(found ? " SIM" : " NAO");
            }
        }
           
       long endTime = System.currentTimeMillis() - start;

        sc.close();

        saveExecutionFile("847235_arvoreArvore.txt", GlobalVariables.comparisons, GlobalVariables.movements, endTime);
    }
}