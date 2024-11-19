//
//  RecipeView.swift
//  RecipeSaver
//
//  Created by Caleb Song on 10/20/24.
//

import SwiftUI

struct RecipeView: View{
    var recipe: RecipeItem
    var body: some View{
        ScrollView{
            if let imageData = recipe.image, let uiImage = UIImage(data: imageData) {
                Image(uiImage: uiImage).resizable()
                    .scaledToFill()
                    .frame(height: 300)
                    .clipped()
                    .background(LinearGradient(gradient:Gradient(colors: [Color(.gray).opacity(0.3), Color(.gray)]), startPoint: .top, endPoint: .bottom))
                    .ignoresSafeArea(.container, edges: .top)
                    .foregroundColor(.white.opacity(0.7))

            }
            else{
                Image(systemName: "photo")
                    .resizable()
                    .scaledToFit()
                    .frame(width:100, height: 100, alignment: .center)
                    .foregroundColor(.white.opacity(0.7))
                    .frame(maxWidth: .infinity, maxHeight: .infinity)
                }
                
            
            
            VStack(spacing: 30){
                Text(recipe.name)
                    .font(.largeTitle)
                    .bold()
                    .multilineTextAlignment(.center)
                VStack(alignment: .leading, spacing: 30){
                    if !recipe.recipeDescription.isEmpty{
                        Text(recipe.recipeDescription)
                    }
                    if !recipe.ingredients.isEmpty{
                        VStack(alignment: .leading, spacing: 20){
                            Text("Ingredients")
                                .font(.headline)
                            Text(recipe.ingredients)
                        }
                    }
                    if !recipe.directions.isEmpty{
                        VStack(alignment: .leading, spacing: 20){
                            Text("Directions")
                                .font(.headline)
                            Text(recipe.directions)
                        }
                    }
                    Text("Favorite").font(.headline)
                    if recipe.favorite {
                        Text("Yes")
                    } else {
                        Text("No")
                    }
                    
                }
                .frame(maxWidth: .infinity, alignment: .leading)
            }
            .padding(.horizontal)
        }
    }
}


//struct RecipeView_Previews: PreviewProvider{
//    static var previews: some View{
//        RecipeView(recipe: Recipe.all[0])
//    }
//}

