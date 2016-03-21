public class InsertionSort{

	public static void swap(int [] array, int j, int i){
		int k = array[j];
		array[j] = array[i];
		array[i] = k;

	}

	public static void insertionSort(int[] array){
		for(int i = 1; i < array.length; i++){
			int j = i-1;
        	for(; j >= 0; j--){
        		if(array[i] < array[j]){
        			swap(array, j, i);
        			i--;
        		}else
        			break;
        	}
    	}
    	for(int i = 0; i < array.length; i++){
    	System.out.print(array[i] + ", ");

    	}
    	System.out.println();
	}


}