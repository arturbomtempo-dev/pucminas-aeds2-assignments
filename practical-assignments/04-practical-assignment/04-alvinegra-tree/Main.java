import java.text.SimpleDateFormat;
import java.text.ParseException;
import java.io.RandomAccessFile;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.io.FileReader;
import java.util.Scanner;
import java.util.Locale;
import java.util.Arrays;
import java.util.Date;


/**
 * TP04Q04 - Árvore Alvinegra
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 29/11/2024
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
        int i = 0;

        Pokemon returnedPokemon = new Pokemon();

        for (i = 0; i < 801; i++) {
            if (pokemon[i].getId() == id) {
                returnedPokemon = pokemon[i];
            }
        }

        return returnedPokemon;
    }

    /**
     * Realiza a troca de posição entre dois Pokémon no array.
     *
     * @param i O índice do primeiro Pokémon.
     * @param j O índice do segundo Pokémon.
     * @return O número de movimentações realizadas (sempre 3 neste caso).
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
    public GlobalVariables() {
        comparisons = 0;
        movements = 0;
    }

    /**
     * Retorna o valor atual do contador de comparações.
     *
     * @return O número total de comparações realizadas.
     */
    public static int getComparisons() {
        return comparisons;
    }

    /**
     * Retorna o valor atual do contador de movimentações.
     *
     * @return O número total de movimentações realizadas.
     */
    public static int getMovements() {
        return movements;
    }
}

/**
 * Classe que representa um nó em uma árvore alvinegra (AN).
 * Cada nó armazena um objeto do tipo Pokemon, uma cor (preto ou branco),
 * e referências para os filhos esquerdo e direito.
 */
class NodeAN {
    public boolean color;
    public Pokemon pokemon;
    public NodeAN left, right;

    /**
     * Construtor que cria um nó alvinegro com cor padrão preta e sem filhos.
     *
     * @param pokemon Objeto Pokemon a ser armazenado no nó.
     */
    public NodeAN(Pokemon pokemon) {
        this(pokemon, false, null, null);
    }

    /**
     * Construtor que cria um nó alvinegro com cor especificada e sem filhos.
     *
     * @param pokemon Objeto Pokemon a ser armazenado no nó.
     * @param color   Cor do nó (true para branco, false para preto).
     */
    public NodeAN(Pokemon pokemon, boolean color) {
        this(pokemon, color, null, null);
    }

    /**
     * Construtor que cria um nó alvinegro com cor, filhos esquerdo e direito especificados.
     *
     * @param pokemon Objeto Pokemon a ser armazenado no nó.
     * @param color   Cor do nó (true para branco, false para preto).
     * @param left    Referência para o nó filho esquerdo.
     * @param right   Referência para o nó filho direito.
     */
    public NodeAN(Pokemon pokemon, boolean color, NodeAN left, NodeAN rigAn) {
        this.color = color;
        this.pokemon = pokemon;
        this.left = left;
        this.right = right;
    }
}

/**
 * Classe que representa uma Árvore Alvinegra, implementando operações
 * básicas como busca, percurso e inserção balanceada de elementos.
 */
class AlvinegraTree{
    private NodeAN root;

    /**
     * Construtor da árvore alvinegra, inicializando a raiz como nula.
     */
    public AlvinegraTree() {
        root = null;
    }

    /**
     * Realiza a busca de um Pokémon na árvore alvinegra a partir do nome.
     *
     * @param name Nome do Pokémon a ser buscado.
     * @return True se o Pokémon for encontrado, false caso contrário.
     */
    public boolean search(String name) {
        System.out.println(name);
        System.out.print("raiz ");
        return search(name, root);
    }

    /**
     * Método recursivo auxiliar para buscar um Pokémon na árvore.
     *
     * @param name Nome do Pokémon a ser buscado.
     * @param i    Nó atual na busca recursiva.
     * @return True se o Pokémon for encontrado, false caso contrário.
     */
    private boolean search(String name, NodeAN i) {
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

    /**
     * Realiza um percurso pré-ordem na árvore, exibindo os nomes dos Pokémon.
     */
    public void walkPre() {
		walkPre(root);
	}

    /**
     * Método recursivo auxiliar para o percurso pré-ordem.
     *
     * @param i Nó atual durante o percurso.
     */
    private void walkPre(NodeAN i) {
        if (i != null) {
			System.out.println(i.pokemon.getName());
			walkPre(i.left);
			walkPre(i.right);
		}
    }

    /**
     * Insere um novo Pokémon na árvore alvinegra.
     *
     * @param pokemon Objeto Pokémon a ser inserido.
     * @throws Exception Se o Pokémon já estiver presente na árvore.
     */
    public void insert(Pokemon pokemon) throws Exception {
        if (root == null) {
            root = new NodeAN(pokemon);
        } else if (root.left == null && root.right == null) {
            if (pokemon.getName().compareTo(root.pokemon.getName()) < 0) {
                GlobalVariables.comparisons++;
                root.left = new NodeAN(pokemon);
            } else {
                GlobalVariables.comparisons += 2;
                root.right = new NodeAN(pokemon);
            }
        } else if(root.left == null) {
            if (pokemon.getName().compareTo(root.pokemon.getName()) < 0) {
                GlobalVariables.comparisons++;
                root.left = new NodeAN(pokemon);
            } else if (pokemon.getName().compareTo(root.right.pokemon.getName()) < 0) {
                GlobalVariables.comparisons++;
                root.left = new NodeAN(root.pokemon);
                root.pokemon = pokemon;
                GlobalVariables.movements++;
            } else {
                GlobalVariables.comparisons += 2;
                root.left = new NodeAN(root.pokemon);
                root.pokemon = root.right.pokemon;
                root.right.pokemon = pokemon;
                GlobalVariables.movements += 2;
            }

            root.left.color = root.right.color = false;
        } else if (root.right == null) {
            if (pokemon.getName().compareTo(root.pokemon.getName()) > 0) {
                GlobalVariables.comparisons++;
                root.right = new NodeAN(pokemon);
            } else if (pokemon.getName().compareTo(root.left.pokemon.getName()) > 0) {
                GlobalVariables.comparisons++;
                root.right = new NodeAN(root.pokemon);
                root.pokemon = pokemon;
                GlobalVariables.movements++;
            } else {
                GlobalVariables.comparisons += 2;
                root.right = new NodeAN(root.pokemon);
                root.pokemon = root.left.pokemon;
                root.left.pokemon = pokemon;
                GlobalVariables.movements += 2;
            }

            root.left.color = root.right.color = false;
        } else {
            insert(pokemon, null, null, null, root);
        }

        root.color = false;
    }

    /**
     * Insere um Pokémon na subárvore de forma balanceada.
     *
     * @param pokemon Pokémon a ser inserido.
     * @param greatGrandfather Nó bisavô.
     * @param grandfather Nó avô.
     * @param father Nó pai.
     * @param i Nó atual.
     * @throws Exception Se o Pokémon já estiver na árvore.
     */
    private void insert(Pokemon pokemon, NodeAN greatGrandfather, NodeAN grandfather, NodeAN father, NodeAN i) throws Exception {
        if (i == null) {
            if (pokemon.getName().compareTo(father.pokemon.getName()) < 0) {
                i = father.left = new NodeAN(pokemon, true);
            } else {
                i = father.right = new NodeAN(pokemon, true);
            }   

            if (father.color == true) {
                balance(greatGrandfather, grandfather, father, i);
            }
        } else {
            if (i.left != null && i.right != null && i.left.color == true && i.right.color == true) {
                i.color = true;
                i.left.color = i.right.color = false;

                if (i == root) {
                    i.color = false;
                } else if (father.color == true) {
                    balance(greatGrandfather, grandfather, father, i);
                }
            }

            if (pokemon.getName().compareTo(i.pokemon.getName()) < 0) {
                insert(pokemon, grandfather, father, i, i.left);
            } else if (pokemon.getName().compareTo(i.pokemon.getName()) > 0) {
                insert(pokemon, grandfather, father, i, i.right);
            } else {
                throw new Exception("Erro ao inserir - Pokemon repetido.");
            }
        }
    }

    /**
     * Realiza o balanceamento da árvore após uma inserção.
     *
     * @param greatGrandfather Nó bisavô.
     * @param grandfather Nó avô.
     * @param father Nó pai.
     * @param i Nó atual.
     */
    private void balance(NodeAN greatGrandfather, NodeAN grandfather, NodeAN father, NodeAN i) {
        if (father.color == true) {
            if (father.pokemon.getName().compareTo(grandfather.pokemon.getName()) > 0) {
                if (i.pokemon.getName().compareTo(father.pokemon.getName()) > 0) {
                    grandfather = leftRotation(grandfather);
                } else {
                    grandfather = rightLeftRotation(grandfather);
                }
            } else {
                if (i.pokemon.getName().compareTo(father.pokemon.getName()) < 0) {
                    grandfather = rightRotation(grandfather);
                } else {
                    grandfather = leftRightRotation(grandfather);
                }
            }

            if (greatGrandfather == null) {
                root = grandfather;
            } else if (grandfather.pokemon.getName().compareTo(greatGrandfather.pokemon.getName()) < 0) {
                greatGrandfather.left = grandfather;
            } else {
                greatGrandfather.right = grandfather;
            }

            grandfather.color = false;
            grandfather.left.color = grandfather.right.color = true;
        }
    }

    /**
     * Realiza uma rotação simples à direita.
     *
     * @param node Nó onde será realizada a rotação.
     * @return Novo nó raiz após a rotação.
     */
    private NodeAN rightRotation(NodeAN node) {
        NodeAN leftNode = node.left;
        NodeAN leftRightNode = leftNode.right;
      
        leftNode.right = node;
        node.left = leftRightNode;

        GlobalVariables.movements += 4;

        return leftNode;
    }
    
    /**
     * Realiza uma rotação simples à esquerda.
     *
     * @param node Nó onde será realizada a rotação.
     * @return Novo nó raiz após a rotação.
     */
    private NodeAN leftRotation(NodeAN node) {
        NodeAN rightNode = node.right;
        NodeAN rightLeftNode = rightNode.left;
      
        rightNode.left = node;
        node.right = rightLeftNode;

        GlobalVariables.movements += 4;

        return rightNode;
    }
      
    /**
     * Realiza uma rotação dupla direita-esquerda.
     *
     * @param node Nó onde será realizada a rotação.
     * @return Novo nó raiz após a rotação.
     */
    private NodeAN rightLeftRotation(NodeAN node) {
        node.right = rightRotation(node.right);
        return leftRotation(node);
    }
    
    /**
     * Realiza uma rotação dupla esquerda-direita.
     *
     * @param node Nó onde será realizada a rotação.
     * @return Novo nó raiz após a rotação.
     */
    private NodeAN leftRightRotation(NodeAN node) {
        node.left = leftRotation(node.left);
        return rightRotation(node);
    }
}

/**
 * Classe principal que implementa a lógica de execução do programa.
 * Gerencia a leitura de dados, operações de inserção e busca em uma árvore alvinegra,
 * além de registrar estatísticas de execução.
 */
public class Main {
    /**
     * Salva o arquivo com as estatísticas de execução.
     *
     * @param filename    Nome do arquivo a ser salvo.
     * @param comparisons Número de comparações realizadas.
     * @param movements   Número de movimentações realizadas.
     * @param endTime     Tempo total de execução em milissegundos.
     */
    public static void saveExecutionFile(String filename, int comparisons, int movements, long endTime) {
        try (RandomAccessFile file = new RandomAccessFile(filename, "rw")) {
            file.writeChars("847235\t"+ comparisons + "\t" + movements + "\t" + endTime +"ms");
            file.close();
        } catch (IOException err) {
            System.err.println("Erro no arquivo criado: " + err.getMessage());
        }
    }

    /**
     * Verifica se a entrada representa o comando "FIM".
     *
     * @param input String de entrada.
     * @return True se a entrada for "FIM", false caso contrário.
     */
    public static boolean isEnd(String input) {
        return (input.length() == 3 && input.charAt(0) == 'F' && input.charAt(1) == 'I' && input.charAt(2) == 'M');
    }

    /**
     * Método principal que gerencia a execução do programa.
     *
     * @param args Argumentos passados pela linha de comando.
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        boolean stop = true;
        
        ManagePokemon mp = new ManagePokemon();

        mp.readPokemon();

        AlvinegraTree pokemonTree = new AlvinegraTree();
        long start = System.currentTimeMillis();
                
        while (stop) {
            String input = sc.nextLine();
            
            if (isEnd(input)) {
                stop = false;
            } else {
                int id = Integer.parseInt(input);
                   
                try {
                    Pokemon pokemon = mp.searchPokemon(id);
                    pokemonTree.insert(pokemon);
                } catch(Exception e){
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

        saveExecutionFile("847235_avinegra.txt", GlobalVariables.getComparisons(), GlobalVariables.getMovements(), endTime);
    }
}