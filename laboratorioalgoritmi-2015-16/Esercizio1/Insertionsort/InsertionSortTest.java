import java.util.*;
import org.junit.Test;
import static org.junit.Assert.assertArrayEquals;

public class InsertionSortTest{

	public static void testInsertionSortOnEmptyArray(){
		int[] array = {};
		InsertionSort.insertionSort(array);
		//assertArrayEquals( new int[]{}, InsertionSort.insertionSort(array));	
	}

	public static void testInsertionSortOnNullArray(){

		
	}

	public static void testInsertionSortOnFullArray(){
		int[] array = {5,3,10,7,2,4,6,1};
		InsertionSort.insertionSort(array);

  }
	}

	public static void testInsertionSortOnEqualsElements(){
		int[] array = {5,5,5,5,5,5,5,5};
		InsertionSort.insertionSort(array);
		System.out.println("OK!");
	}

	public static void main (String[] args){
		testInsertionSortOnEmptyArray();
		testInsertionSortOnNullArray();
		testInsertionSortOnFullArray();
		testInsertionSortOnEqualsElements();
		
	}

}