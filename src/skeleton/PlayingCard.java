package skeleton;

/**
 * PlayingCard.java
 */

/**
 * This class as given represents a playing card with Suits but no Rank. Your
 * job is to implement Ranks by creating the code described at the TODO markers.
 * 
 * @author Mitch Parry
 * @version May 6, 2013
 */
public class PlayingCard
{
    // Fields
    // TODO: Declare a SuitsAndRanks.Suit variable named suit;

    // TODO: Declare a SuitsAndRanks.Rank variable named rank;

    /**
     * Constructor - each card assigned a rank and suit when created by the Deck
     * class.
     * 
     */
    // TODO: Create constructor with first parameter 'rank' and second
    // parameter 'suit'
    public PlayingCard(/* put parameters here */)
    {
        // TODO: Assign suit passed via constructor to field suit

        // TODO: Assign rank passed via constructor to field rank

    }

    /**
     * Getter method that returns this card's Suit.
     * 
     * @return Suit of this card
     */
    // TODO: Write a getter method that returns this card's Suit
    public SuitsAndRanks.Suit getSuit()
    {
        return SuitsAndRanks.Suit.CLUBS;
    }

    /**
     * Getter method that returns this card's Rank.
     * 
     * @return Rank of this card
     */
    // TODO: Write a getter method that returns this card's Rank

    /**
     * Sets the suit of the card.
     * 
     * @param suit
     *            The new suit for this card
     */
    // TODO: Write a setter method for this card's Suit.
    public void setSuit(SuitsAndRanks.Suit suit)
    {
    }

    /**
     * Sets the rank of this card.
     * 
     * @param rank
     *            The new rank for this card
     */
    // TODO: Write a setter method for this card's Rank.

    /*
     * TODO: Override the toString method to return a string in the following
     * format: "Rank Suit".
     */
    /**
     * Returns a String representation of a PlayingCard.
     * 
     * @return The string.
     */
    @Override
    public String toString()
    {
        return "";
    }
}
