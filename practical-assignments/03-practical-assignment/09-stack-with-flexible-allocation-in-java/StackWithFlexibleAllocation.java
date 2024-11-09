import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.Locale;
import java.util.Scanner;
import java.io.RandomAccessFile;

/**
 * TP03Q09 - Pilha com Alocação Flexível em Java
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 09/11/2024
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
     * @return ID do Pokémon.
     */
    public int getId() {
        return this.id;
    }

    /**
     * Define o ID do Pokémon.
     * @param id Novo ID do Pokémon.
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * Obtém a geração do Pokémon.
     * @return Geração do Pokémon.
     */
    public int getGeneration() {
        return this.generation;
    }

    /**
     * Define a geração do Pokémon.
     * @param generation Nova geração do Pokémon.
     */
    public void setGeneration(int generation) {
        this.generation = generation;
    }

    /**
     * Obtém o nome do Pokémon.
     * @return Nome do Pokémon.
     */
    public String getName() {
        return this.name;
    }

    /**
     * Define o nome do Pokémon.
     * @param name Novo nome do Pokémon.
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Obtém a descrição do Pokémon.
     * @return Descrição do Pokémon.
     */
    public String getDescription() {
        return this.description;
    }

    /**
     * Define a descrição do Pokémon.
     * @param description Nova descrição do Pokémon.
     */
    public void setDescription(String description) {
        this.description = description;
    }

    /**
     * Obtém a lista de tipos do Pokémon.
     * @return Lista de tipos do Pokémon.
     */
    public ArrayList<String> getTypes() {
        return this.types;
    }

    /**
     * Define a lista de tipos do Pokémon.
     * @param types Nova lista de tipos do Pokémon.
     */
    public void setTypes(ArrayList<String> types) {
        this.types = types;
    }

    /**
     * Obtém a lista de habilidades do Pokémon.
     * @return Lista de habilidades do Pokémon.
     */
    public ArrayList<String> getAbilities() {
        return this.abilities;
    }

    /**
     * Define a lista de habilidades do Pokémon.
     * @param abilities Nova lista de habilidades do Pokémon.
     */
    public void setAbilities(ArrayList<String> abilities) {
        this.abilities = abilities;
    }

    /**
     * Obtém o peso do Pokémon.
     * @return Peso do Pokémon.
     */
    public double getWeight() {
        return this.weight;
    }

    /**
     * Define o peso do Pokémon.
     * @param weight Novo peso do Pokémon.
     */
    public void setWeight(double weight) {
        this.weight = weight;
    }

    /**
     * Obtém a altura do Pokémon.
     * @return Altura do Pokémon.
     */
    public double getHeight() {
        return this.height;
    }

    /**
     * Define a altura do Pokémon.
     * @param height Nova altura do Pokémon.
     */
    public void setHeight(double height) {
        this.height = height;
    }

    /**
     * Obtém a taxa de captura do Pokémon.
     * @return Taxa de captura do Pokémon.
     */
    public int getCaptureRate() {
        return this.captureRate;
    }

    /**
     * Define a taxa de captura do Pokémon.
     * @param captureRate Nova taxa de captura do Pokémon.
     */
    public void setCaptureRate(int captureRate) {
        this.captureRate = captureRate;
    }

    /**
     * Obtém se o Pokémon é lendário.
     * @return {@code true} se o Pokémon é lendário; caso contrário, {@code false}.
     */
    public boolean getIsLegendary() {
        return this.isLegendary;
    }

    /**
     * Define se o Pokémon é lendário.
     * @param isLegendary {@code true} se o Pokémon é lendário; caso contrário, {@code false}.
     */
    public void setIsLegendary(boolean isLegendary) {
        this.isLegendary = isLegendary;
    }

    /**
     * Obtém a data de captura do Pokémon.
     * @return Data de captura do Pokémon.
     */
    public Date getCaptureDate() {
        return this.captureDate;
    }

    /**
     * Define a data de captura do Pokémon.
     * @param captureDate Nova data de captura do Pokémon.
     */
    public void setCaptureDate(Date captureDate) {
        this.captureDate = captureDate;
    }

    /**
     * Cria uma cópia deste Pokémon com os mesmos valores de atributos.
     * 
     * @return Nova instância de {@code Pokemon} com valores copiados.
     */
    public Pokemon Clone() {
        return new Pokemon(
            this.id,
            this.generation,
            this.name,
            this.description,
            this.types,
            this.abilities,
            this.weight,
            this.height,
            this.captureRate,
            this.isLegendary,
            this.captureDate
        );
    }
}

/**
 * Representa uma célula em uma estrutura de dados encadeada que armazena um objeto do tipo Pokemon.
 */
class Cell {
    public Pokemon pokemon;
    public Cell next;

    /**
     * Construtor padrão da classe Cell.
     * Inicializa a célula com um valor nulo para o Pokémon e para a próxima célula.
     */
    public Cell() {
        this(null);
    }

    /**
     * Construtor que inicializa uma célula com um Pokémon específico.
     *
     * @param pokemon Instância de Pokemon a ser armazenada nesta célula.
     */
    public Cell(Pokemon pokemon) {
        this.pokemon = pokemon;
        this.next = null;
    }
}

/**
 * Classe que representa uma pilha de objetos do tipo Pokemon.
 */
class Stack {
    private Cell top;
    private int size;

    /**
     * Construtor da pilha. Inicializa a pilha vazia.
     */
    public Stack() {
        top = null;
    }

    /**
     * Insere um novo Pokemon no topo da pilha.
     *
     * @param pokemon Instância de Pokemon a ser inserida.
     */
    public void insert(Pokemon pokemon) {
        Cell temp = new Cell(pokemon);
        temp.next = top;
        top = temp;
        temp = null;
        size++;
    }

    /**
     * Remove e retorna o Pokemon do topo da pilha.
     *
     * @return O Pokemon removido do topo da pilha.
     * @throws Exception Se a pilha estiver vazia.
     */
    public Pokemon remove() throws Exception {
        if (top == null) {
            throw new Exception("Erro ao remover.");
        }

        Pokemon response = top.pokemon;
        Cell temp = top;
        top = top.next;
        temp.next = null;
        temp = null;
        size--;

        return response;
    }

    /**
     * Exibe os elementos da pilha na saída padrão.
     */
    public void show() {
        show(top, 0);
    }

    /**
     * Método auxiliar recursivo para exibir os elementos da pilha.
     *
     * @param i     Célula atual da pilha.
     * @param count Índice de posição atual do elemento.
     */
    private void show(Cell i, int count) {
        if (i != null) {
            show(i.next, ++count);

            SimpleDateFormat outputDateFormat = new SimpleDateFormat("dd/MM/yyyy");
            String formattedDate = outputDateFormat.format(i.pokemon.getCaptureDate());

            System.out.println("[" + (size - count) + "] [#"
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
        }
    }
}

/**
 * Classe responsável por gerenciar operações relacionadas aos objetos Pokemon.
 * Inclui métodos para criar, ler e buscar Pokemons a partir de dados externos.
 */
class ManagePokemon {
    private static Pokemon pokemon[] = new Pokemon[801];

    /**
     * Cria um objeto Pokemon a partir de uma linha de texto.
     *
     * @param linha Linha do arquivo CSV que contém os dados do Pokemon.
     * @return Um objeto Pokemon com os dados preenchidos a partir da linha fornecida.
     */
    public Pokemon createPokemon(String linha) {
        Pokemon pokemon = new Pokemon();
        SimpleDateFormat ddf = new SimpleDateFormat("dd/MM/yyyy", Locale.ENGLISH);
        String[] fields = linha.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)");

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
     * Lê os dados do arquivo CSV e preenche o array de Pokemons.
     *
     * @return Um array de objetos Pokemon contendo os dados lidos do arquivo CSV.
     */
    public Pokemon[] readCsv() {
        int i = 0;

        try (BufferedReader br = new BufferedReader(new FileReader("/tmp/pokemon.csv"))) {
            String line = br.readLine(); // Ignora o cabeçalho
            line = br.readLine();

            while (line != null) {
                pokemon[i++] = createPokemon(line);
                line = br.readLine();
            }
        } catch (IOException e) {
            System.out.println("Erro ao ler o arquivo: " + e.getMessage());
        }

        return pokemon;
    }

    /**
     * Busca um Pokemon pelo seu ID no array de Pokemons.
     *
     * @param id O ID do Pokemon a ser buscado.
     * @return Um objeto Pokemon com o ID fornecido ou um Pokemon vazio caso não seja encontrado.
     */
    public Pokemon searchPokemon(int id) {
        Pokemon responsePokemon = new Pokemon();

        for (int i = 0; i < 801; i++) {
            if (pokemon[i].getId() == id) {
                responsePokemon = pokemon[i];
                break;
            }
        }

        return responsePokemon;
    }
}

/**
 * Classe principal para gerenciamento de operações em uma pilha de Pokémons
 * com alocação flexível, realizando inserções e remoções com base em comandos.
 */
public class StackWithFlexibleAllocation {
    public static int comparisons;  // Contador de comparações durante as operações
    public static int movements;    // Contador de movimentos durante as operações

    /**
     * Salva as estatísticas de execução (comparações, movimentos e tempo) em um arquivo.
     *
     * @param filename   Nome do arquivo onde os dados serão salvos.
     * @param comparisons Número total de comparações realizadas.
     * @param movements   Número total de movimentos realizados.
     * @param endTime     Tempo total de execução em milissegundos.
     */
    public static void saveExecutionFile(String filename, int comparisons, int movements, long endTime) {
        try (RandomAccessFile file = new RandomAccessFile(filename, "rw")) {
            file.writeChars("847235\t" + comparisons + "\t" + movements + "\t" + endTime + "ms");
            file.close();
        } catch (IOException err) {
            System.err.println("Erro ao criar arquivo." + err.getMessage());
        }
    }

    /**
     * Verifica se a entrada indica o fim dos dados.
     *
     * @param input String de entrada a ser verificada.
     * @return true se a entrada for "FIM", false caso contrário.
     */
    public static boolean isEnd(String input) {
        return (input.length() == 3 && input.charAt(0) == 'F' && input.charAt(1) == 'I' && input.charAt(2) == 'M');
    }

    /**
     * Método principal que lê as entradas do usuário, executa operações na pilha de Pokémons
     * e salva as estatísticas de execução.
     *
     * @param args Argumentos de linha de comando.
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        boolean stop = true;
        int i = 0;
        int k = 0;

        ManagePokemon mp = new ManagePokemon();
        mp.readCsv();

        Stack pokemonsStack = new Stack();
        Pokemon deletedPokemons[] = new Pokemon[20];

        // Loop para inserir Pokémons na pilha com base nas entradas do usuário
        while (stop) {
            String input = sc.nextLine();

            if (isEnd(input)) {
                stop = false;
            } else {
                int id = Integer.parseInt(input);

                try {
                    Pokemon poke = mp.searchPokemon(id);
                    pokemonsStack.insert(poke);
                    i++;
                } catch (Exception e) {
                    System.out.println("Pokemon não encontrado: " + e.getMessage());
                }
            }
        }

        int operationsNumber = sc.nextInt();
        long start = System.currentTimeMillis();

        // Loop para processar operações na pilha de acordo com os comandos fornecidos
        for (int j = 0; j < operationsNumber; j++) {
            String operation = sc.next();
            comparisons++;

            if (operation.equals("I")) {
                int number = sc.nextInt();

                try {
                    movements++;
                    pokemonsStack.insert(mp.searchPokemon(number));
                } catch (Exception e) {
                    System.out.println("Pokemon não encontrado: " + e.getMessage());
                }
            } else {
                comparisons++;
            }

            if (operation.equals("R")) {
                try {
                    movements++;
                    deletedPokemons[k++] = pokemonsStack.remove();
                } catch (Exception e) {
                    System.out.println("Lista vazia: " + e.getMessage());
                }
            }
        }

        long endTime = System.currentTimeMillis() - start;

        // Exibe os Pokémons removidos
        for (int j = 0; j < k; j++) {
            System.out.println("(R) " + deletedPokemons[j].getName());
        }

        // Exibe o conteúdo da pilha
        pokemonsStack.show();

        sc.close();

        // Salva as estatísticas de execução
        saveExecutionFile("847235_PilhaFlexivel.txt", comparisons, movements, endTime);
    }
}