import java.util.*;

public class InsertionSortTest{

	public static void test_insertion_sort_on_empty_array(){
		int[] array = {};
		InsertionSort.insertionSort(array);
		//assertArrayEquals( new int[]{}, InsertionSort.insertionSort(array));	
	}

	public static void test_insertion_sort_on_null_array(){

		
	}

	public static void test_insertion_sort_on_full_array(){
		int[] array = {5,3,10,7,2,4,6,1};
		InsertionSort.insertionSort(array);

  }
	}

	public static void test_insertion_sort_on_equals_elements(){
		int[] array = {5,5,5,5,5,5,5,5};
		InsertionSort.insertionSort(array);
		System.out.println("OK!");
	}

	public static void main (String[] args){
		test_insertion_sort_on_empty_array();
		test_insertion_sort_on_null_array();
		test_insertion_sort_on_full_array();
		test_insertion_sort_on_equals_elements();
		
	}

}