 
import javax.swing.JOptionPane;
 
 
public class OnlinePurchaseCalculator {
 
    public static void main(String[] args) {
 
        // Define variables
 
        String itemName;
 
        double itemCost;
 
        int quantity;
 
        double total, tax, shipping, totalDue;
 
 
        // Prompt for and read the data using dialog boxes
 
        itemName = JOptionPane.showInputDialog("Enter the name of the item:");
 
        String costInput = JOptionPane.showInputDialog("Enter the cost of the item:");
 
        itemCost = Double.parseDouble(costInput);
 
        String quantityInput = JOptionPane.showInputDialog("Enter the quantity of the item:");
 
        quantity = Integer.parseInt(quantityInput);
 
 
        // Performing calculations
 
        total = itemCost * quantity;
 
        tax = total * 0.07;
 
        shipping = total * 0.01;
 
        totalDue = total + tax + shipping;
 
 
        // Create output statements with updated address
 
        System.out.println("Ship to:");
 
        System.out.println("Naveen Robert");
 
        System.out.println("456 Elm Street");
 
        System.out.println("Springfield, IL 62701");
 
        System.out.println();
 
        System.out.println("Item: \t\t" + itemName);
 
        System.out.println("Item price: \t" + itemCost);
 
        System.out.println("Quantity: \t" + quantity);
 
        System.out.println("Total: \t\t" + total);
 
        System.out.println("Tax: \t\t" + tax);
 
        System.out.println("Shipping: \t" + shipping);
 
        System.out.println("Total Due: \t" + totalDue);
 
    }
 
}
 

