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

class NodeAN {
    public boolean color;
    public Pokemon pokemon;
    public NodeAN left, right;
    
    public NodeAN(Pokemon pokemon) {
        this(pokemon, false, null, null);
    }
    
    public NodeAN(Pokemon pokemon, boolean color) {
        this(pokemon, color, null, null);
    }
    
    public NodeAN(Pokemon pokemon, boolean color, NodeAN left, NodeAN right) {
        this.color = color;
        this.pokemon = pokemon;
        this.left = left;
        this.right = right;
    }
}

class AlvinegraTree{
    private NodeAN root;
    
    public AlvinegraTree() {
        root = null;
    }
    
    public boolean search(String name) {
        System.out.println(name);
        System.out.print("raiz ");
        return search(name, root);
    }
    
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
    
    public void walkPre() {
		walkPre(root);
	}
    
    private void walkPre(NodeAN i) {
        if (i != null) {
			System.out.println(i.pokemon.getName());
			walkPre(i.left);
			walkPre(i.right);
		}
    }
    
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
    
    private NodeAN rightRotation(NodeAN node) {
        NodeAN leftNode = node.left;
        NodeAN leftRightNode = leftNode.right;
      
        leftNode.right = node;
        node.left = leftRightNode;

        GlobalVariables.movements += 4;

        return leftNode;
    }
    
    private NodeAN leftRotation(NodeAN node) {
        NodeAN rightNode = node.right;
        NodeAN rightLeftNode = rightNode.left;
      
        rightNode.left = node;
        node.right = rightLeftNode;

        GlobalVariables.movements += 4;

        return rightNode;
    }
    
    private NodeAN rightLeftRotation(NodeAN node) {
        node.right = rightRotation(node.right);
        return leftRotation(node);
    }
    
    private NodeAN leftRightRotation(NodeAN node) {
        node.left = leftRotation(node.left);
        return rightRotation(node);
    }
}

public class Main {
    public static void saveExecutionFile(String filename, int comparisons, int movements, long endTime) {
        try (RandomAccessFile file = new RandomAccessFile(filename, "rw")) {
            file.writeChars("847235\t"+ comparisons + "\t" + movements + "\t" + endTime +"ms");
            file.close();
        } catch (IOException err) {
            System.err.println("Erro no arquivo criado: " + err.getMessage());
        }
    }
    
    public static boolean isEnd(String input) {
        return (input.length() == 3 && input.charAt(0) == 'F' && input.charAt(1) == 'I' && input.charAt(2) == 'M');
    }
    
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

        saveExecutionFile("847235_avinegra.txt", GlobalVariables.comparisons, GlobalVariables.movements, endTime);
    }
}