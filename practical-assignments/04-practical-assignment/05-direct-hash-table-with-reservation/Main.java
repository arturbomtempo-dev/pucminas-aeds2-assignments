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
 * TP04Q05 - Tabela Hash Direta com Reserva
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 03/12/2024
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
}

/**
 * Classe que implementa uma tabela hash com gerenciamento de colisões por reserva.
 * Utiliza a função de hash baseada na soma dos valores ASCII dos caracteres do nome do Pokémon.
 * A tabela é dividida em duas partes: a principal e a reserva.
 */
class Hash {
    private Pokemon table[];
    int m1, m2, m, reserve;
    final Pokemon NULL = new Pokemon();

    /**
     * Construtor padrão da classe Hash.
     * Inicializa a tabela hash com 21 posições na parte principal e 9 na reserva.
     */
    public Hash() {
        this(21, 9);
    }

    /**
     * Construtor que permite definir tamanhos personalizados para a tabela hash.
     *
     * @param m1 Tamanho da tabela principal.
     * @param m2 Tamanho da área de reserva.
     */
    public Hash(int m1, int m2) {
        this.m1 = m1;
        this.m2 = m2;
        this.m = m1 + m2;
        this.table = new Pokemon[this.m];

        for (int i = 0; i < m; i++) {
            table[i] = NULL;
        }
        
        reserve = 0;
    }

    /**
     * Função de hash que calcula a posição baseada no nome do Pokémon.
     * Soma os valores ASCII de cada caractere do nome e calcula o módulo com o tamanho da tabela principal.
     *
     * @param name Nome do Pokémon.
     * @return Posição calculada na tabela principal.
     */
    public int h(String name) {
        int sum = 0;
        for (int i = 0; i < name.length(); sum += (int) name.charAt(i), i++);
        return  sum % m1;
    }

    /**
     * Insere um Pokémon na tabela hash.
     * Verifica primeiro a tabela principal e, em caso de colisão, utiliza a área de reserva.
     *
     * @param pokemon Pokémon a ser inserido.
     * @return True se o Pokémon foi inserido com sucesso, false caso contrário.
     */
    public boolean insert(Pokemon pokemon) {
        boolean response = false;

        if (pokemon != NULL) {
            GlobalVariables.comparisons++;
            int position = h(pokemon.getName());

            if (table[position] == NULL) {
                GlobalVariables.comparisons++; 
                table[position] = pokemon;
                response = true;
            } else if (reserve < m2) {
                GlobalVariables.comparisons++; 
                table[m1 + reserve] = pokemon;
                reserve++;
                response = true; 
            }
        }

        return response;
    }

    /**
     * Busca um Pokémon pelo nome na tabela hash.
     * Primeiro verifica a tabela principal; em seguida, pesquisa na área de reserva.
     *
     * @param name Nome do Pokémon a ser buscado.
     * @return A posição do Pokémon na tabela, ou -1 se não for encontrado.
     */
    public int search(String name) {
        boolean response = false;
        int position = h(name);
        int responsePosition = 0;

        if (table[position].getName().equals(name)) {
            GlobalVariables.comparisons++;
            response = true;
            responsePosition = position;
        } else if (table[position] != NULL) {
            GlobalVariables.comparisons++;
            for (int i = 0; i < reserve; i++) {
                if (table[m1 + i].getName().equals(name)) {
                    GlobalVariables.comparisons++;
                    response = true;
                    responsePosition = (m1 + i);
                    i = reserve;
                }
            }
        }

        return response ? responsePosition : -1;
    }
}
 
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
        } catch(IOException err) {
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
     * Método principal que gerencia a leitura, inserção e busca de Pokémon utilizando uma tabela hash.
     * O programa é dividido em duas fases principais: inserção e busca. Na fase de inserção, os Pokémon
     * são carregados a partir de um arquivo e inseridos na tabela hash. Durante a fase de busca, o usuário
     * fornece nomes de Pokémon, e o programa verifica se eles estão presentes na tabela hash.
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        boolean stop = true;
        
        ManagePokemon mp = new ManagePokemon();

        mp.readPokemon();

        Hash table = new Hash();
        long start = System.currentTimeMillis();
                
        while (stop) {
            String input = sc.nextLine();
            
            if (isEnd(input)) {
                stop = false;
            } else {
                int id = Integer.parseInt(input);

                try {
                    Pokemon pokemon = mp.searchPokemon(id);
                    table.insert(pokemon);
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
                int response = table.search(input);
                System.out.println("=> " + input + ": " + (response != -1 ? "(Posicao: "+ response +") SIM" : "NAO"));
            }
        }
           
        long endTime = System.currentTimeMillis() - start;

        sc.close();

        saveExecutionFile("847235_hashReserva.txt", GlobalVariables.comparisons, GlobalVariables.movements, endTime);
    }
}