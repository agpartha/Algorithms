public class Reverse
{

    /**
     * Reverse a list
     *
     * @param head the pointer to the original list
     * @return a pointer to a reversed list
     */
    public Node reverse( Node head )
    {
        if ( head == null )
        {
            return head;
        }    
        
        // Initial position of the triplet
        Node currentN  = head;
        Node nextN     = head.next;
        Node previousN = null;
        

        while ( true )
        {
            // Switch pointer direction
            currentN.next = previousN;
            
            if ( nextN == null )
            { // Are we done?
                break;
            }    
            
            // Move the triplet one step down the list
            previousN  = currentN;
            currentN   = nextN;
            nextN      = nextN.next;
        } 
        return currentN;
    }
}    
