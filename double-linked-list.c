struct model
{
	/*list related members*/
	void *last_entry;
	void *next_entry;

	/*
	*
	*
	*	DATA
	*
	*/
};



struct model *initial_entry=NULL;
struct model *current_entry=NULL;
struct model *selected_entry=NULL;



struct model* gfx_create_model_entry()
{
	/*create a new entry if no entry exists yet*/
	if(initial_entry==NULL)
	{
		initial_entry=malloc(sizeof(struct model));
			
		/*initializing data*/
		initial_entry->last_entry=NULL;
		initial_entry->next_entry=NULL;

		/*
		*
		*	DATA
		*
		*/

		return initial_entry;
	}

	current_entry=initial_entry;
	
	/*looking for the last entry*/
	while(current_entry->next_entry!=NULL)
	{
		current_entry=current_entry->next_entry;
	}
	
	
	/*creating a new entry*/
	current_entry->next_entry=malloc(sizeof(struct model));
	
	void* last_entry=current_entry;
	
	/*initializing data*/
	current_entry=current_entry->next_entry;
	/*marking it as the last entry*/
	current_entry->next_entry=NULL; 
	current_entry->last_entry=last_entry;

		/*
		*
		*	DATA
		*
		*/
	
	return current_entry;
}

int gfx_select_entry(struct model* entry_address)
{
	selected_entry=entry_address;
	if(selected_entry->next_entry==NULL)
	{
		return EOT;
	}
	return TABLE_OK;
}

struct model* gfx_select_first_entry()
{
	selected_entry=initial_entry;
	return selected_entry;
}

struct model* gfx_next_entry()
{
	if(selected_entry->next_entry==NULL)
	{
		return EOT;
	}
	selected_entry=selected_entry->next_entry;
	return selected_entry;
}

struct model* gfx_copy_model(struct model* entry_address)
{
	struct model *new_entry=gfx_create_model_entry();

	void *next_entry_save=new_entry->next_entry;
	void *last_entry_save=new_entry->last_entry;

	*new_entry=*entry_address;

	new_entry->next_entry=next_entry_save;
	new_entry->last_entry=last_entry_save;
	
	return new_entry;
}

void gfx_delete_model_entry(struct model* entry_address)
{
	current_entry=entry_address;
	struct model *previous_entry;
	struct model *next_entry;
	
	/*if this is the only entry*/
	if(current_entry->last_entry==NULL && current_entry->next_entry==NULL)
	{
		initial_entry=NULL;
		free(current_entry);
		return;
	}
	
	/*if this is simply the first entry*/
	if(current_entry->last_entry==NULL && current_entry->next_entry!=NULL)
	{
		initial_entry=current_entry->next_entry;
		current_entry=current_entry->next_entry;
		free(current_entry->last_entry);
		current_entry->last_entry=NULL;
		return;
	}
	
	/*if this is an entry in the middle*/
	if(current_entry->last_entry!=NULL && current_entry->next_entry!=NULL)
	{
		previous_entry=current_entry->last_entry;
		previous_entry->next_entry=current_entry->next_entry;
		
		next_entry=current_entry->next_entry;
		next_entry->last_entry=current_entry->last_entry;
		
		free(current_entry);
		return;
	}
	
	/*if this is the last entry in the list*/
	if(current_entry->last_entry!=NULL && current_entry->next_entry==NULL)
	{
		previous_entry=current_entry->last_entry;
		previous_entry->next_entry=NULL;
		free(current_entry);
		return;
	}
}

void gfx_model_list_cleanup()
{
	struct model *current_entry=initial_entry;

	while(1)
	{
		if(current_entry->next_entry!=NULL)
		{
			current_entry=current_entry->next_entry;
			free(current_entry->last_entry);
		}
		else
		{
			free(current_entry);
			break;
		}		
	}
	return;
}