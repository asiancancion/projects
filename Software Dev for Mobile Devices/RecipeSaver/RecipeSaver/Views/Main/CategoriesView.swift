//
//  CategoriesView.swift
//  RecipeSaver
//
//  Created by Caleb Song on 10/20/24.
//

import SwiftUI
import SwiftData

struct CategoriesView: View{
//    @Binding var recipes: [Recipe]
    @Query private var recipes: [RecipeItem]
    var body: some View{
        NavigationView {
            List{
                ForEach(Category.allCases){ category in
                    NavigationLink{
                        CategoryView(category: category)
                    }
                    label:{
                        Text(category.rawValue + "s")
                    }
                }
            }
            .navigationTitle("Categories")
        }
        .navigationViewStyle(.stack)
    }
}


struct CategoriesView_Previews: PreviewProvider{
    @State static var recipes: [Recipe] = Recipe.all
    static var previews: some View{
        CategoriesView()
    }
}

