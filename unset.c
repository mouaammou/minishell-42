/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 04:45:35 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/01 05:44:49 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_list_env **env, char *key)
{
	t_list_env	*prev;
	t_list_env	*curr;

	prev = NULL;
	curr = *env;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->data.key, key) == 0)
		{
			if (prev == NULL) // first node
			{
				*env = curr->next;
			}
			else
			{
				prev->next = curr->next;
			}
			free_node(curr);
			global_exit.exit_status = 0;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
	// key not found, do nothing
	global_exit.exit_status = 1;
}


// void deleteN(Node** head, int position)
// {
//     Node* temp;
//     Node* prev;
//     temp = *head;
//     prev = *head;
//     for (int i = 0; i < position; i++) {
//         if (i == 0 && position == 1) {
//             *head = (*head)->next;
//             free(temp);
//         }
//         else {
//             if (i == position - 1 && temp) {
//                 prev->next = temp->next;
//                 free(temp);
//             }
//             else {
//                 prev = temp;
 
//                 // Position was greater than
//                 // number of nodes in the list
//                 if (prev == NULL)
//                     break;
//                 temp = temp->next;
//             }
//         }
//     }
// }

// void deleteN(t_list_env **env, char *key)
// {
// 	t_list_env	*temp;
// 	t_list_env	*prev;

//     temp = *env;
//     prev = *env;
//     int i = 0;
    
//     while (i < position) {
//         if (i == 0 && position == 1) {
//             *head = (*head)->next;
//             free(temp);
//         }
//         else {
//             if (i == position - 1 && temp) {
//                 prev->next = temp->next;
//                 free(temp);
//             }
//             else {
//                 prev = temp;
 
//                 // Position was greater than
//                 // number of nodes in the list
//                 if (prev == NULL)
//                     break;
//                 temp = temp->next;
//             }
//         }
        
//         i++;
//     }
// }

// void deleteNode(struct Node** head_ref, int key)
// {
//     // Store head node
//     struct Node *temp = *head_ref, *prev;
 
//     // If head node itself holds the key to be deleted
//     if (temp != NULL && temp->data == key) {
//         *head_ref = temp->next; // Changed head
//         free(temp); // free old head
//         return;
//     }
 
//     // Search for the key to be deleted, keep track of the
//     // previous node as we need to change 'prev->next'
//     while (temp != NULL && temp->data != key) {
//         prev = temp;
//         temp = temp->next;
//     }
 
//     // If key was not present in linked list
//     if (temp == NULL)
//         return;
 
//     // Unlink the node from linked list
//     prev->next = temp->next;
 
//     free(temp); // Free memory
// }

// void ft_unset(t_list_env **env, char *key)
// {
//     // Store head node
//     t_list_env *temp;
// 	t_list_env *prev;

// 	temp = *env;
//     // If head node itself holds the key to be deleted
//     if (temp != NULL && ft_strcmp(temp->data.key, key) == 0) {
//         *env = temp->next; // Changed head
//         free(temp); // free old head
//         return;
//     }
 
//     // Search for the key to be deleted, keep track of the
//     // previous node as we need to change 'prev->next'
//     while (temp != NULL && ft_strcmp(temp->data.key, key) == 0) {
//         prev = temp;
//         temp = temp->next;
//     }
 
//     // If key was not present in linked list
//     if (temp == NULL)
//         return;
 
//     // Unlink the node from linked list
//     prev->next = temp->next;
 
//     free(temp); // Free memory
// }