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
    
    public int getId() {
        return this.id;
    }
    
    public void setId(int id) {
        this.id = id;
    }
    
    public int getGeneration() {
        return this.generation;
    }
    
    public void setGeneration(int generation) {
        this.generation = generation;
    }
    
    public String getName() {
        return this.name;
    }
    
    public void setName(String name) {
        this.name = name;
    }
    
    public String getDescription() {
        return this.description;
    }
    
    public void setDescription(String description) {
        this.description = description;
    }
    
    public ArrayList<String> getTypes() {
        return this.types;
    }
    
    public void setTypes(ArrayList<String> types) {
        this.types = types;
    }
    
    public ArrayList<String> getAbilities() {
        return this.abilities;
    }
    
    public void setAbilities(ArrayList<String> abilities) {
        this.abilities = abilities;
    }
    
    public double getWeight() {
        return this.weight;
    }
    
    public void setWeight(double weight) {
        this.weight = weight;
    }

    public double getHeight() {
        return this.height;
    }
    
    public void setHeight(double height) {
        this.height = height;
    }

    public int getCaptureRate() {
        return this.captureRate;
    }

    public void setCaptureRate(int captureRate) {
        this.captureRate = captureRate;
    }
    
    public boolean getIsLegendary() {
        return this.isLegendary;
    }
    
    public void setIsLegendary(boolean isLegendary) {
        this.isLegendary = isLegendary;
    }
    
    public Date getCaptureDate() {
        return this.captureDate;
    }
    
    public void setCaptureDate(Date captureDate) {
        this.captureDate = captureDate;
    }
}

class ManagePokemon {
    private static Pokemon pokemon[] = new Pokemon[801];
    
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
    
    public Pokemon[] readPokemon() {
        int i = 0;
 
        try (BufferedReader br = new BufferedReader(new FileReader("../tmp/pokemon.csv"))) {
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
    
    public int swap(int i, int j) {
        Pokemon temp = pokemon[i];
        pokemon[i] = pokemon[j];
        pokemon[j] = temp; 
        
        return 3;
    }
}

class GlobalVariables {
    public static int comparisons;
    public static int movements;
    
    public GlobalVariables(){
        comparisons = 0;
        movements = 0;
    }
}

class Node {
    public int element;
    public Node left, right;
    public Node2 other;
    
    public Node(int element) {
        this.element = element;
        this.left = this.right = null;
        this.other = null;
    }
    
    public Node(int element, Node left, Node right) {
        this.element = element;
        this.left = left;
        this.right = right;
    }
}

class Node2 {
    public Pokemon pokemon;
    public Node2 left, right;
    
    public Node2(Pokemon pokemon) {
        this.pokemon = pokemon;
        this.left = this.right = null;
    }
    
    public Node2(Pokemon pokemon, Node2 left, Node2 right) {
        this.pokemon = pokemon;
        this.left = left;
        this.right = right;
    }
}

class BinaryTreeBinaryTrees {
    private Node root;
    
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
    
    public void insert(int element) throws Exception {
        root = insert(element, root);
    }
    
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
    
    public void insert(Pokemon pokemon) throws Exception {
        insert(pokemon, root);
    }
    
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
    
    public boolean search(String name) {
        System.out.println("=> " + name);
        System.out.print("raiz ");
        return walkPre(name, root);
    }
    
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

public class Main {
    public static void saveExecutionFile(String filename, int comparisons, int movements, long endTime) {
        try (RandomAccessFile file = new RandomAccessFile(filename, "rw")) {
            file.writeChars("847235" + "\t" +  endTime + "ms" + "\t" + comparisons);
            file.close();
        } catch(IOException err) {
            System.err.println("Erro Node arquivo criado: " + err.getMessage());
        }
    }
    
    public static boolean isEnd(String input) {
        return (input.length() == 3 && input.charAt(0) == 'F' && input.charAt(1) == 'I' && input.charAt(2) == 'M');
    }
    
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