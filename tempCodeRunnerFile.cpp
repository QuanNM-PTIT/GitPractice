if(!IdB.empty()){
		cout << "Danh sach cac sach da muon:\n";
		for(int x: IdB){
			for(auto temp: v){
				if (temp.getId() == x){
					temp.print();
				}
			}
		}
	}